if ARGV.size == 0
    puts "error: no input"
    exit
end

def insert_num(seen : Hash(Int32, Bool), nums : Hash(Int32, Array(Int32)), num : Int32, turn : Int32)
    if nums.has_key?(num)
        nums[num] << turn
        if nums[num].size > 2
            nums[num].shift()
        end
    else
        nums[num] = [turn]
    end
    if seen.has_key?(num)
        seen[num] = false
    else
        seen[num] = true
    end
    return num
end

def solve(count_to : Int32, pt : Char)
    starting = ARGV[0].split(',')
    seen = Hash(Int32, Bool).new
    nums = Hash(Int32, Array(Int32)).new
    total = 0
    turn = 0
    last = -1
    while total != count_to
        turn += 1
        if starting.size != 0
            num = starting.shift().to_i()
            last = insert_num(seen, nums, num, turn)
        else
            if seen[last]
                last = insert_num(seen, nums, 0, turn)
            else
                num = turn - 1 - nums[last][0]
                last = insert_num(seen, nums, num, turn)
            end
        end
        total += 1
    end
    puts "pt.#{pt}: #{nums.select{|num, t| t.includes?(count_to)}.keys[0]}"
end

solve(2020, '1')
solve(30000000, '2')
