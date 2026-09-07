fn sum(values: Int[]) -> Int {
    var total = 0;

    for x in values {
        total += x;
    }

    return total;
}

let numbers = [1, 2, 3, 4, 5];

print(sum(numbers));
