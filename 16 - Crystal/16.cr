enum Mode : UInt8
    Field = 0x01
    Ticket = 0x02
    Nearby = 0x03
end

struct FieldRange
    property min, max

    def initialize(@min : Int32, @max : Int32)
    end
end

struct Field
    property name, ranges

    def initialize(@name : String, @ranges : Array(FieldRange))
    end
end

def get_lines
    lines = Array(String).new
    File.each_line "input.txt" do |line|
        lines << line
    end
    return lines
end

def next_mode(mode : Mode)
    if mode == Mode::Field
        return Mode::Ticket
    elsif mode == Mode::Ticket
        return Mode::Nearby
    end
    abort "Unknown Mode"
end

def parse_tickets(line : String, target : Array(Int32))
    tickets = line.split(',')
    tickets.each do |t|
        t = t.to_i?()
        if !t
            next
        end
        target << t
    end
end

def parse_input(lines : Array(String))
    fields = Array(Field).new
    your_tickets = Array(Int32).new
    nearby = Array(Array(Int32)).new
    nearby_all = Array(Int32).new
    mode = Mode::Field
    lines.each do |line|
        if line == ""
            mode = next_mode(mode)
        end
        if mode == Mode::Field
            line = line.split(": ")
            ranges = line[1].split(" or ")
            range_objects = Array(FieldRange).new
            ranges.each do |str|
                range = str.split('-')
                min = range[0].to_i()
                max = range[1].to_i()
                range_objects << FieldRange.new(min, max)
            end
            field = Field.new(line[0], range_objects)
            fields << field
        elsif mode == Mode::Ticket
            parse_tickets(line, your_tickets)
        elsif mode == Mode::Nearby
            if line.empty? || line.starts_with?('n')
                next
            end
            parse_tickets(line, nearby_all)
            nearby << line.split(',').map { |x| x.to_i() }
        end
    end
    return fields, your_tickets, nearby_all, nearby
end

def get_ranges(fields : Array(Field))
    ranges = Array(FieldRange).new
    fields.each do |field|
        ranges += field.ranges
    end
    return ranges
end

def get_invalid_tickets(ranges : Array(FieldRange), nearby : Array(Int32))
    invalid_tickets = Array(Int32).new
    nearby.each do |ticket|
        if ranges.all? { |r| !(r.min <= ticket && ticket <= r.max) }
            invalid_tickets << ticket
        end
    end
    return invalid_tickets
end

def solve(lines : Array(String))
    fields, your_tickets, nearby_all, nearby = parse_input(lines)
    ranges = get_ranges(fields)
    invalid_tickets = get_invalid_tickets(ranges, nearby_all)
    puts "pt.1: #{invalid_tickets.sum()}"
    nearby = nearby.reject { |ticket| ticket.any? { |t| invalid_tickets.any? { |i| t == i } } }
    false_positions = Hash(String, Array(Int32)).new
    nearby.each do |ticket|
        ticket.each_with_index do |num, i|
            fields.each do |field|
                r1 = field.ranges[0]
                r2 = field.ranges[1]
                if !(r1.min <= num && num <= r1.max) && !(r2.min <= num && num <= r2.max)
                    if false_positions.has_key?(field.name)
                        false_positions[field.name] << i
                    else
                        false_positions[field.name] = [i]
                    end
                end
            end
        end
    end
    actual_positions = Hash(String, Int32).new
    sorted_positions = false_positions.to_a.sort_by{ |_k, v| v.size }.map{ |k, v| { k => v.sort } }.reverse
    sorted_positions.each do |pos|
        i = 0
        actual_positions.each_value do |v|
            pos.first_value << v
        end
        pos.first_value.sort!
        pos.first_value.each do |num|
            if num != i
                actual_positions[pos.first_key] = i
                break
            end
            i += 1
        end
    end
    actual_positions.select! { |name, _v| name.starts_with?("departure")}
    multiply = UInt64.new(1)
    actual_positions.each do |name, pos|
        multiply *= your_tickets[pos]
    end
    puts "pt.2: #{multiply}"
end

lines = get_lines()
solve(lines)
