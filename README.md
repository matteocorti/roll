# roll

roll is a program to roll dices specified in a simple and intuitive way.

![](https://img.shields.io/github/v/release/matteocorti/roll)&nbsp;![](https://img.shields.io/github/downloads/matteocorti/roll/latest/total)&nbsp;![](https://img.shields.io/github/downloads/matteocorti/roll/total)&nbsp;![](https://img.shields.io/github/license/matteocorti/roll)&nbsp;![](https://img.shields.io/github/stars/matteocorti/roll)&nbsp;![](https://img.shields.io/github/forks/matteocorti/roll)

see INSTALL on how to compile and install roll and the man page for instructions

## Synopsis

```
roll [-hpsv] [--version] expression
```

## Description

Rolls a user-defined dice sequence. The dices to roll are defined using `dN` where `N` is the number of sides. Dices can be rolled multiple times by prepending the number of repetitions (e.g., `3d6`) and used in simple mathematical expressions (e.g., `2d8+4`).

## Options

```
--help, -h
       help

--positive, -p
       allow only positive results

--sum-series, -s
       show the sum of roll series

--verbose, -v
       verbose (displays the result for each roll)

--version
       prints the version of the program
```

## Expressions

Expressions are in dice notation (also known as dice algebra, common dice notation or RPG dice notation).

Die rolls are expressed in the form `NdX` or `NDX` where `N` is the number of dices (`1` if omitted) and `X` the number of dice faces.

roll also accepts `W` (German) or `T` (Swedish) to specify a dice (`D` in English)

If the final number is omitted, it is assumed to be a six.

To this basic notation, an additive modifier can be appended, yielding expressions of the form, `NdX+C`. The plus can be replaced by a minus sign ("`-`") for subtraction. `C` is a number to be added subtracted from the final total.

See: [http://en.wikipedia.org/wiki/Dice_notation](http://en.wikipedia.org/wiki/Dice_notation)

### Percentile dice (`d%`)

Often, the variable `X` in the above notation will be "`%`". Although a 100-sided die does exist, it is both more common and more uniformly random to use a combination of two ten-sided dice known as percentile dice, where one die  represents tens and the other units.  A roll of two zeroes means 100.

If you want to roll a single 100-sided die use the "`d100`" notation.

### d10x

d10x is equivalent to d10 x d10 and gives a non-linear distribution.

### Fudge dice (`dF` or `df`)

The Fudge role-playing game system uses customized "Fudge dice" which have an equal number of plus, minus and blank sides.

### Multipliers

In some games, the above notation is expanded to allow for a multiplier, as in `NdXxC` or `CxNdX`, where "`x`" or "`*`" denotes multiplication (can be replaced by "`/`" for division) and `C` is a natural number.

Results are rounded up.

### Reroll filters

It  is possible to specify restrictions on dice rolls telling which values to keep and which values to discard by putting a filter after the dice. If a value is to be discarded the dice is re-rolled until the result is valid value. You can specify to keep only values bigger (`>`), bigger or equal (`>=`), smaller (`<`), smaller or equal (`<=`) or different (`!=`) from a given number. The comparator is specified right after the the die specification (e.g., `1D6>2`).

### Selective results

It is possible to keep only the `M` highest or lowest dices with the following notation:

 * `NdXhM`: roll `N` dices with `X` sides and keep the highest `M` results (`M` must be less or equal `N`)
 * `NdXkM`: `K` for keep is equivalent to `H` for highest
 * `NdXlM`: roll `N` dices with `X` sides and keep the lowest `M` results (`M` must be less or equal `N`)

Or using the abbreviated notation `NdX-L` to drop the lowest and `NdX-H` to drop the highest result.

### Series and repetitions

It is possible to concatenate top-level expressions with a comma ("`expression, expression`") and to repeat the execution of an expression or a set of expressions by using a counter and curly brackets ("`N{ expression}`")

### Examples

```
3d6        rolls 3 6-sided dices and sums the results
           (can be abbreviated with "3d")
1d8 + 3    rolls 1 8-sided die and adds 3
                  (can be abbreviated by "d8+3")
d%         rolls 2 10-sided dices: one represents the tens and
           the other units
1d6x5      rolls 1 6-sided dice and multiplies the result by 5
1d6 / 2    rolls 1 6-sided dice and divides the result by 2 (1d3)
4d6h3      rolls 4 6-sided dices and keeps the 3 highest results
           (discarding the lowest)
4d6LX      rolls 4 6-sided dices and discards the lowest
"6{3d6}"   rolls 3d6 6 times (expression
           is quoted to avoid the { and { being interpreted
           by the shell)
"1d6>2"    rolls 1d6 until the result is bigger than 2 (expression
           is quoted to avoid the > being interpreted as
           redirection by the shell)
4DF        rolls 4 Fudge dices
```



### Grammar (EBNF)

```
expression   := term { "+" term | "-" term } .
term         := number | factor [ ("*"|"x"|"/") number |
                number ("*"|"/") factor | "(" expression ")" .
factor       := number FilteredDice [ ("h"|"H"|"l"|"L"|"k"|"K") number ] | number FiltreredDice ("h"|"H"|"l"|"L") ("X") | FilteredDice .
FilteredDice := dice | dice (">"|">="|"<"|"<="|"!=") number .
dice         := "d" | "D" | "w" | "W" | "t" | "T" [ number | "%" | "F" | "f" | "X" ]
```

