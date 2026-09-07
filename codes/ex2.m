fn sum(values: Int[]) -> Int {
    var total = 0;

    // sum each number in array
    for x in values {
        total += x;
    }

    // return sum total
    return total;
}

let numbers = [1, 2, 3, 4, 5];

print(sum(numbers));
