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
    let bag = bags[checkBag]
    if bag.len == 0:
        return
    for name, bagContents in bag:
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

let lines = readFile("input.txt").splitLines()
var bags = initTable[string, Table[string, int]]()
parseBags(lines, bags)
solvePt1(bags)
