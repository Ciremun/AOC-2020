import sequtils, sugar
import strutils
import tables

proc parseBags(lines: seq[string], bags: var Table[string, Table[string, int]]) =
    for line in lines:
        let lineSplit = line.split(' ')
        let bag = lineSplit[0 .. 1].join("")
        if not bags.hasKey(bag):
            bags[bag] = initTable[string, int]()
        var bagContents = lineSplit[4 .. ^2]
        bagContents = bagContents.join(" ").split(',').map(x => strip(x))
        for bagType in bagContents:
            if bagType == "no other":
                continue
            let bagTypeSplit = bagType.split(' ')
            let bagName = bagTypeSplit[1 .. 2].join("")
            let bagCount = parseInt(bagTypeSplit[0])
            bags[bag][bagName] = bagCount

proc countShiny(bags: var Table[string, Table[string, int]], checkBag: string,
                isShiny: var Table[string, bool], current: var string) =
    for name, bagContents in bags[checkBag]:
        if name == "shinygold":
            isShiny[current] = true
        countShiny(bags, name, isShiny, current)

proc solvePt1(bags: var Table[string, Table[string, int]]) =
    var current = ""
    var isShiny = initTable[string, bool]()
    for name in bags.keys:
        current = name
        countShiny(bags, name, isShiny, current)
    var pt1 = 0
    for shiny in isShiny.values:
        if shiny:
            inc(pt1)
    echo "pt.1: ", pt1

proc sum(bag: Table[string, int]): int =
    var total = 1
    for count in bag.values:
        total += count
    return total

proc countBags(bags: var Table[string, Table[string, int]], checkBag: string): Table[string, int] =
    var bagsInside = initTable[string, int]()
    for name, count in bags[checkBag]:
        bagsInside[name] = count * sum(countBags(bags, name))
    return bagsInside

proc solvePt2(bags: var Table[string, Table[string, int]]) =
    let bagsInside = countBags(bags, "shinygold")
    echo "pt.2: ", sum(bagsInside) - 1

let linesP1 = readFile("p1.txt").splitLines()
let linesP2 = readFile("p2.txt").splitLines()
var bags = initTable[string, Table[string, int]]()
parseBags(linesP1, bags)
solvePt1(bags)
clear(bags)
parseBags(linesP2, bags)
solvePt2(bags)
