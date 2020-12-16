$lines = IO.readlines('input.txt')

def possible_bin_combinations(length)
    combinations = []
    for i in 0..2**length - 1 do
        combination = i.to_s(2)
        if combination.length < length
            combination = "#{zeros_string(length - combination.length)}#{combination}"
        end
        combinations << combination
    end
    return combinations
end

def apply_mask_p2(mask, target)
    result = zeros_string(mask.length - 1)
    mask.split('').each_with_index do |bit, i|
        if bit == '0'
            result[i] = target[i]
        elsif bit == '1'
            result[i] = '1'
        elsif bit == 'X'
            result[i] = 'X'
        end
    end
    return result
end

def apply_mask_p1(mask, target)
    result = zeros_string(mask.length - 1)
    mask.split('').each_with_index do |bit, i|
        if bit == 'X'
            result[i] = target[i]
        else
            result[i] = bit
        end
    end
    return result
end

def part_2(mask, mem, mem_pos, mem_val)
    mem_pos_bin = mem_binary(mask, mem_pos)
    mem_pos_result = apply_mask_p2(mask, mem_pos_bin)
    mem_val_bin = mem_binary(mask, mem_val)
    mem_pos_bin_comb = possible_bin_combinations(mem_pos_result.count('X'))
    mem_pos_bin_comb.each do |comb|
        mem_pos_mask = mem_pos_result.dup
        comb.split('').each do |num|
            x_pos = -1
            mem_pos_mask.split('').each_with_index do |bit, i|
                if bit == 'X'
                    x_pos = i
                    break
                end
            end
            mem_pos_mask[x_pos] = num
        end
        mem[mem_pos_mask] = mem_val_bin
    end
end

def mem_binary(mask, mem_val)
    mem_val_bin = mem_val.to_i.to_s(2)
    zeros = zeros_string(mask.length - mem_val_bin.length - 1)
    return "#{zeros}#{mem_val_bin}"
end

def mem_sum(mem)
    sum = 0
    mem.each_value do |mem_val|
        sum += mem_val.to_i(2)
    end
    return sum
end

def zeros_string(length)
    zeros = ""
    for i in 1..length do
        zeros += '0'
    end
    return zeros
end

def part_1(mask, mem, mem_pos, mem_val)
    mem_val_bin = mem_binary(mask, mem_val)
    mem[mem_pos] = apply_mask_p1(mask, mem_val_bin)
end

def solve_part(part)
    mem = {}
    mask = ""
    $lines.each do |line|
        if line.start_with?("mask")
            mask = line[7..]
        else
            mem_pos, mem_val = line[4..].split("] = ")
            part.call(mask, mem, mem_pos, mem_val)
        end
    end
    puts mem_sum(mem)
end

solve_part(method(:part_1))
solve_part(method(:part_2))
