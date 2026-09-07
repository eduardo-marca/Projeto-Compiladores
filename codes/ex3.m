fn isPrime(n: Int) -> Bool {
    if n < 2 {
        return false;
    }

    var i = 2;

    while i * i <= n {
        if n % i == 0 {
            return false;
        }

        i += 1;
    }

    return true;
}

var n = 2;

while n <= 100 {
    if isPrime(n) {
        print(n);
    }

    n += 1;
}
