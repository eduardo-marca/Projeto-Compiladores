var dp : Int[101];

/*
example code with most resources of the language
*/

fn Fibo(n : Int) -> Int {
    if n == 0 or n == 1 {
        return 1;
    }
    if dp[n] == -1 {
        dp[n] = Fibo(n-1) + Fibo(n-2);
    }
    return dp[n];
} 

fn isPrime(n : Int) -> Bool {
    if n <= 2 { return true; }
    var x : Int = 2;
    while x*x <= n {
        if n % x == 0 {
            return false;
        }
        x++;
    }
    return true;
}

fn Sum(A : Int[]) -> Int {
    var sum : Int = 0;
    for x in A {
        sum += x;
    }
    return sum;
}

fn main() -> Void {
    A : Int[] = [1, 2, 3, 4, 5];

    let sum = Sum(A)
    mean : Float = (sum as Float) / length(A);

    mensagem : String = "The mean is: " + mean as String;
    print(mensagem);

    for i in 0..length(dp) {
        dp[i] = -1;
    }

    print("The 100th fibonacci number is " + Fibo(100) as String);

    // calc and print the first (10) primes
    let count = 10;
    var primes : Int[count];
    var i = 0;
    var x = 1;
    while i < count {
        if isPrime(x) {
            primes[i] = x;
            i++;
        }
        x++;
    }

    message = "The first " + count as String + "th primes are: ";
    for p in 0..count {
        message += prime[p] as String;
        if not (p == count-1) {
            message += ", ";
        }
    }
}

main();
