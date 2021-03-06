import java.io.File

fun is_valid_hex_char(c: String): Boolean {
    val c_int: Int? = c.toIntOrNull()
    if (c_int is Int)
        return 0 <= c_int && c_int <= 9
    return listOf("a", "b", "c", "d", "e", "f").contains(c)
}

fun is_valid_field_hair(pd_value: String): Boolean {
    val pd_hash: String = pd_value.substring(0, 1)
    val pd_values: String = pd_value.substring(1, 7)
    if (pd_hash == "#" && pd_values.length == 6 && pd_values.all{ is_valid_hex_char(it.toString()) })
        return true
    return false
}

fun is_valid_field_height(pd_value: String): Boolean {
    if (pd_value.endsWith("cm") && is_valid_field_range(pd_value.substring(0, 3), 150, 193))
        return true
    if (pd_value.endsWith("in") && is_valid_field_range(pd_value.substring(0, 2), 59, 76))
        return true
    return false
}

fun is_valid_field_range(pd_value: String, x: Int, y: Int): Boolean {
    val pd_int: Int? = pd_value.toIntOrNull()
    return pd_int is Int && (x <= pd_int && pd_int <= y)
}

fun is_valid_passport(pd: MutableMap<String, String>, puzzle_part: Int): Boolean {
    if (puzzle_part == 1) return pd.all{ (k, v) -> k == "cid" || listOf("byr","iyr","eyr","hgt","hcl","ecl","pid").contains(k) && !v.isEmpty() }
    for (i in pd.keys) {
        if (i == "cid") continue
        val pd_value: String? = pd.get(i)
        if (pd_value is String && !pd_value.isEmpty()) {
            when (i) {
                "byr" -> if (pd_value.length != 4 || !is_valid_field_range(pd_value, 1920, 2002)) return false
                "iyr" -> if (pd_value.length != 4 || !is_valid_field_range(pd_value, 2010, 2020)) return false
                "eyr" -> if (pd_value.length != 4 || !is_valid_field_range(pd_value, 2020, 2030)) return false
                "hgt" -> if (pd_value.length <= 3 || !is_valid_field_height(pd_value)) return false
                "hcl" -> if (pd_value.length != 7 || !is_valid_field_hair(pd_value)) return false
                "ecl" -> if (pd_value.length != 3 || !listOf("amb","blu","brn","gry","grn","hzl","oth").contains(pd_value)) return false
                "pid" -> if (pd_value.length != 9 || !pd_value.all{ it.toString().toIntOrNull() is Int }) return false
            }
        }
        else return false
    }
    return true
}

fun main() {
    val inp: String = File("input.txt").readText() + "\n"
    val lines: List<String> = inp.split("\n").map{ it.trim() }
    val passports: MutableList<String> = mutableListOf()
    var passport_str: String = ""
    var valid_passports_p1: Int = 0
    var valid_passports_p2: Int = 0
    for (line in lines) {
        if (line.isEmpty()) {
            passports.add(passport_str)
            passport_str = ""
            continue
        }
        if (passport_str.isEmpty()) passport_str = line
        else passport_str = "$passport_str $line"
    }
    for (passport in passports) {
        val pd: MutableMap<String, String> = mutableMapOf(
            "byr" to "", "iyr" to "", "eyr" to "",
            "hgt" to "", "hcl" to "", "ecl" to "",
            "pid" to "", "cid" to "")
        val field_pairs: List<String> = passport.split(" ")
        for (pair in field_pairs) {
            val pair_split: List<String> = pair.split(":")
            val field_key: String = pair_split[0]
            val field_val: String = pair_split[1]
            pd.put(field_key, field_val)
        }
        if (is_valid_passport(pd, 1)) valid_passports_p1++
        if (is_valid_passport(pd, 2)) valid_passports_p2++
    }
    println("pt.1: $valid_passports_p1")
    println("pt.2: $valid_passports_p2")
}
