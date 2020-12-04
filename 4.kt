import java.io.File

// detecting which passports have all required fields

// input.txt:

// pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
// hcl:#623a2f

// eyr:2029 ecl:blu cid:129 byr:1989
// iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

// hcl:#888785
// hgt:164cm byr:2001 iyr:2015 cid:88
// pid:545766238 ecl:hzl
// eyr:2022

// iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719

// Valid Passports: 4


fun is_valid_hex_char(c: String): Boolean
{
    val c_int: Int? = c.toIntOrNull()
    if (c_int is Int)
    {
        return 0 <= c_int && c_int <= 9
    }
    else
    {
        val valid_hex_chars: List<String> = listOf("a", "b", "c", "d", "e", "f")
        return valid_hex_chars.contains(c)
    }
}


fun is_valid_field_hair(pd_value: String): Boolean
{
    val pd_hash = pd_value.substring(0, 1)
    val pd_values = pd_value.substring(1, 7)
    if (pd_hash == "#" && pd_values.length == 6 && pd_values.all{ is_valid_hex_char(it.toString()) })
        return true
    return false
}


fun is_valid_field_height(pd_value: String): Boolean
{
    if (pd_value.endsWith("cm") && is_valid_field_range(pd_value.substring(0, 3), 150, 193))
        return true
    else if (pd_value.endsWith("in") && is_valid_field_range(pd_value.substring(0, 2), 59, 76))
        return true
    return false
}


fun is_valid_field_range(pd_value: String, x: Int, y: Int): Boolean
{
    val pd_int: Int? = pd_value.toIntOrNull()
    if (pd_int !is Int || !(x <= pd_int && pd_int <= y))
        return false
    return true
}


fun is_valid_passport(pd: MutableMap<String, String>): Boolean
{
    for (i in pd.keys)
    {
        if (i == "cid") continue
        val pd_value: String? = pd.get(i)
        if (pd_value is String)
        {
            if (pd_value.isEmpty())
                return false
            if (     i == "byr" && (pd_value.length != 4 || !is_valid_field_range(pd_value, 1920, 2002)))
                return false
            else if (i == "iyr" && (pd_value.length != 4 || !is_valid_field_range(pd_value, 2010, 2020)))
                return false
            else if (i == "eyr" && (pd_value.length != 4 || !is_valid_field_range(pd_value, 2020, 2030)))
                return false
            else if (i == "hgt" && (pd_value.length <= 3 || !is_valid_field_height(pd_value)))
                return false
            else if (i == "hcl" && (pd_value.length != 7 || !is_valid_field_hair(pd_value)))
                return false
            else if (i == "ecl" && (pd_value.length != 3 || !listOf("amb", "blu", "brn", "gry", "grn", "hzl", "oth").contains(pd_value)))
                return false
            else if (i == "pid" && (pd_value.length != 9 || !pd_value.all{ it.toString().toIntOrNull() is Int }))
                return false
        }
        else
        {
            return false
        }
    }
    return true
}


fun main() {
    val inp: String = File("input.txt").readText() + "\n"
    val lines: List<String> = inp.split("\n").map{ it.trim() }
    val passports: MutableList<String> = mutableListOf()
    var passport_str: String = ""
    var valid_passports: Int = 0;

    for (line in lines)
    {
        if (line.isEmpty())
        {
            passports.add(passport_str)
            passport_str = ""
            continue
        }
        if (passport_str.isEmpty())
            passport_str = line
        else
            passport_str = "$passport_str $line"
    }

    for (passport in passports)
    {
        val pd: MutableMap<String, String> = mutableMapOf(
            "byr" to "", "iyr" to "", "eyr" to "",
            "hgt" to "", "hcl" to "", "ecl" to "",
            "pid" to "", "cid" to "")
        val field_pairs: List<String> = passport.split(" ")
        for (pair in field_pairs)
        {
            val pair_split: List<String> = pair.split(":")
            val field_key: String = pair_split[0]
            val field_val: String = pair_split[1]
            pd.put(field_key, field_val)
        }
        if (is_valid_passport(pd)) valid_passports++
    }
    println("Valid Passports: $valid_passports")
}
