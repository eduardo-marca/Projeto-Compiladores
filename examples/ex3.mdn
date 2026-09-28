// function to verify if a number is prime
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

// find the first 100 primes
while n <= 100 {
    if isPrime(n) {
        print(n);
    }

    n += 1;
}
