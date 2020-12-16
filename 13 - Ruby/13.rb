lines = IO.readlines('input.txt')

def part1(lines)
    timestamp = lines.shift().to_i
    buses = []
    earliest_busID = 1
    earliest_arrival = 2147483647
    lines[0].split(',').each do |busID|
        if busID != 'x'
            busID = busID.to_i
            arrives_at = 1
            i = 1
            while arrives_at < timestamp
                arrives_at = busID * i
                i += 1
            end
            if arrives_at < earliest_arrival
                earliest_arrival = arrives_at
                earliest_busID = busID
                buses << arrives_at
            end
        end
    end
    puts "pt.1: #{(earliest_arrival - timestamp) * earliest_busID}"
end

part1(lines)
