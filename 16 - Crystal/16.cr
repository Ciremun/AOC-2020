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
    lines = [] of String
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

def parse_input(lines : Array(String))
    fields = Array(Field).new
    ticket = nil
    nearby = Array(Int32).new
    mode = Mode::Field
    lines.each do |line|
        if line == ""
            mode = next_mode(mode)
        end
        if mode == Mode::Field
            line = line.split(": ")
            ranges = line[1].split(" or ")
            range_objects = [] of FieldRange
            ranges.each do |str|
                range = str.split('-')
                min = range[0].to_i()
                max = range[1].to_i()
                range_objects << FieldRange.new(min, max)
            end
            field = Field.new(line[0], range_objects)
            fields << field
        elsif mode == Mode::Ticket
            next
        elsif mode == Mode::Nearby
            nearby_tickets = line.split(',')
            nearby_tickets.each do |t|
                t = t.to_i?()
                if !t
                    next
                end
                nearby << t
            end
        end
    end
    return fields, nearby
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

def solve1(lines : Array(String))
    fields, nearby = parse_input(lines)
    ranges = get_ranges(fields)
    invalid_tickets = get_invalid_tickets(ranges, nearby)
    puts invalid_tickets.sum()
end

lines = get_lines()
solve1(lines)
