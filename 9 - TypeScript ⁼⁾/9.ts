import { readFileSync } from 'fs';

interface PreambleMinMax {
    min: number;
    max: number;
}

interface PreambleData {
    min: number;
    max: number;
    preamble: number;
    preambleNums: number[];
    numbers: number[];
}

let sum = (x: number, y: number): number => { return x + y; };
let ascend = (x: number, y: number): number => { return x - y; };
let getPreambleNums = (numbers: number[], preamble: number): number[] =>
    { return numbers.slice(0, preamble).sort(ascend); }

function validNum(num: number, d: PreambleData) {
    if (d.min <= num && num <= d.max) {
        for (let x of d.preambleNums) {
            for (let y of d.preambleNums) {
                if (x + y == num) return true;
            }
        }
    }
    return false;
}

function preambleMinMax(preambleNums: number[]): PreambleMinMax {
    let min = preambleNums.slice(0, 2).reduce(sum);
    let max = preambleNums.slice(-2).reduce(sum);
    return { min, max };
}

function firstBadNum(d: PreambleData): number {
    while (d.numbers.length > 0) {
        let afterPreamble: number = d.numbers.slice(d.preamble)[0];
        if (!validNum(afterPreamble, d)) return afterPreamble;
        else {
            d.numbers = d.numbers.slice(1);
            d.preambleNums = getPreambleNums(d.numbers, d.preamble);
            let minMax: PreambleMinMax = preambleMinMax(d.preambleNums);
            d.min = minMax.min;
            d.max = minMax.max;
        }
    }
    return -1;
}

function solve(input: string, preamble: number) {
    let numbers: number[] = input.split('\n').map(x => +x);
    if (numbers.length < preamble) return console.log("error: lines length < preamble");
    let preambleNums: number[] = getPreambleNums(numbers, preamble);
    let minMax: PreambleMinMax = preambleMinMax(preambleNums);
    let min: number = minMax.min;
    let max: number = minMax.max;
    let pt1: number = firstBadNum({ min, max, preamble, preambleNums, numbers });
    console.log(pt1);
}
const file = readFileSync('input.txt', 'utf-8');
solve(file, 25);
