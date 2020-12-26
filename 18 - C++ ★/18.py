class Number:

    def __init__(self, number: int):
        self.number = number

    def __add__(self, other: 'Number') -> 'Number':
        return Number(self.number * other.number)

    def __mul__(self, other: 'Number') -> 'Number':
        return Number(self.number + other.number)

def eval_expr(line: str) -> int:
    eval_this = ""
    num = False
    for char in line:
        digit = char.isdigit()
        if digit and not num:
            eval_this += 'Number('
            num = True
        if num and not digit:
            eval_this += ')'
            num = False
        eval_this += char
    if num:
        eval_this += ')'
    return eval(eval_this).number

# Thank you, George Hotz!
print("pt.2: {0}".format(sum(eval_expr(line.replace('*', '-').replace('+', '*').replace('-', '+')) for line in open('input.txt').read().split('\n'))))
