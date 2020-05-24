#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int, int> mii;

ll _sieve_size;
bitset<10000010> bs;                     // 10^7 should be enough for most cases
vll primes;               // compact list of primes in form of vector<long long>


// first part

void sieve(ll upperbound)            // create list of primes in [0..upperbound]
{
    _sieve_size = upperbound+1;                     // add 1 to include upperbound
    bs.set();                                                 // set all bits to 1
    bs[0] = bs[1] = 0;                                     // except index 0 and 1
    for (ll i = 2; i < _sieve_size; i++) if (bs[i])
        {
            // cross out multiples of i <= _sieve_size starting from i*i
            for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
            primes.push_back(i);       // also add this vector containing list of primes
        }
}                                           // call this method in main method

bool isPrime(ll N)                   // a good enough deterministic prime tester
{
    if (N < _sieve_size) return bs[N];                // now O(1) for small primes
    for (int i = 0; (i < primes.size()) && (primes[i]*primes[i] <= N); i++)
        if (N%primes[i] == 0) return false;
    return true;                    // it takes longer time if N is a large prime!
}                      // note: only work for N <= (last prime in vi "primes")^2

// second part

vi primeFactors(ll N)     // remember: vi is vector of integers, ll is long long
{
    vi factors;                    // vi `primes' (generated by sieve) is optional
    ll PF_idx = 0, PF = primes[PF_idx];     // using PF = 2, 3, 4, ..., is also ok
    while ((N != 1) && (PF*PF <= N))     // stop at sqrt(N), but N can get smaller
    {
        while (N%PF == 0)
        {
            N /= PF;    // remove this PF
            factors.push_back(PF);
        }
        PF = primes[++PF_idx];                              // only consider primes!
    }
    if (N != 1) factors.push_back(N);     // special case if N is actually a prime
    return factors;         // if pf exceeds 32-bit integer, you have to change vi
}

// third part

ll numPF(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (N != 1 && (PF*PF <= N))
    {
        while (N%PF == 0)
        {
            N /= PF;
            ans++;
        }
        PF = primes[++PF_idx];
    }
    return ans + (N != 1);
}

ll numDiffPF(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (N != 1 && (PF*PF <= N))
    {
        if (N%PF == 0) ans++;                             // count this pf only once
        while (N%PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    return ans + (N != 1);
}

ll sumPF(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (N != 1 && (PF*PF <= N))
    {
        while (N%PF == 0)
        {
            N /= PF;
            ans += PF;
        }
        PF = primes[++PF_idx];
    }
    return ans + (N != 1) * N;
}

ll numDiv(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1;             // start from ans = 1
    while (N != 1 && (PF*PF <= N))
    {
        ll power = 0;                                             // count the power
        while (N%PF == 0)
        {
            N /= PF;
            power++;
        }
        ans *= (power+1);                                // according to the formula
        PF = primes[++PF_idx];
    }
    return (N != 1) ? 2*ans : ans;    // (last factor has pow = 1, we add 1 to it)
}

ll sumDiv(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1;             // start from ans = 1
    while (N != 1 && (PF*PF <= N))
    {
        ll power = 0;
        while (N%PF == 0)
        {
            N /= PF;
            power++;
        }
        ans *= ((ll)pow((double)PF, power+1.0) - 1) / (PF-1);             // formula
        PF = primes[++PF_idx];
    }
    if (N != 1) ans *= ((ll)pow((double)N, 2.0) - 1) / (N-1);          // last one
    return ans;
}

ll EulerPhi(ll N)
{
    ll PF_idx = 0, PF = primes[PF_idx], ans = N;             // start from ans = N
    while (N != 1 && (PF * PF <= N))
    {
        if (N % PF == 0) ans -= ans / PF;                // only count unique factor
        while (N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    return (N != 1) ? ans - ans/N : ans;                            // last factor
}

int main()
{
    // first part: the Sieve of Eratosthenes
    sieve(10000000);                       // can go up to 10^7 (need few seconds)
    printf("%lld\n", primes.back());            // last prime generated is 9999991
    for (int i = 10000001; ; i++)
        if (isPrime(i))
        {
            printf("The next prime beyond the last prime generated is %d\n", i);
            break;
        }
    printf("%d\n", isPrime((1LL<<31)-1));  // 2^31-1 = 2147483647, 10-digits prime
    printf("%d\n", isPrime(136117223861LL));        // not a prime, 104729*1299709


    // second part: prime factors
    vi r = primeFactors((1LL<<31)-1);   // slowest, 2^31-1 = 2147483647 is a prime
    for (auto &pf : r) printf("> %d\n", pf);
    printf("\n");

    r = primeFactors(136117223861LL);    // slow, 2 large factors 104729 * 1299709
    for (auto &pf : r) printf("> %d\n", pf);
    printf("\n");

    r = primeFactors(142391208960LL);    // faster, 2^10 * 3^4 * 5 * 7^4 * 11 * 13
    for (auto &pf : r) printf("> %d\n", pf);
    printf("\n");

    r = primeFactors(99999820000081LL);             // this is the limit: 9999991^2
    for (auto &pf : r) printf("> %d\n", pf);
    printf("\n");

    // r = primeFactors(100000380000361LL);                 // error, beyond 9999991^2
    // for (auto &pf : r) printf("> %d\n", pf);
    // printf("\n");

    // third part: prime factors variants
    printf("numPF(%d) = %lld\n", 50, numPF(50)); // 2^1 * 5^2 => 3
    printf("numDiffPF(%d) = %lld\n", 50, numDiffPF(50)); // 2^1 * 5^2 => 2
    printf("sumPF(%d) = %lld\n", 50, sumPF(50)); // 2^1 * 5^2 => 2 + 5 + 5 = 12
    printf("numDiv(%d) = %lld\n", 50, numDiv(50)); // 1, 2, 5, 10, 25, 50, 6 divisors
    printf("sumDiv(%d) = %lld\n", 50, sumDiv(50)); // 1 + 2 + 5 + 10 + 25 + 50 = 93
    printf("EulerPhi(%d) = %lld\n", 50, EulerPhi(50)); // 20 integers < 50 are relatively prime with 50
    printf("\n");

    // special cases when N is a prime number
    printf("numPF(%d) = %lld\n", 7, numPF(7)); // 7^1 => 1
    printf("numDiffPF(%d) = %lld\n", 7, numDiffPF(7)); // 7^1 = 1
    printf("sumPF(%d) = %lld\n", 7, sumPF(7)); // 7^1 => 7
    printf("numDiv(%d) = %lld\n", 7, numDiv(7)); // 1 and 7, 2 divisors
    printf("sumDiv(%d) = %lld\n", 7, sumDiv(7)); // 1 + 7 = 8
    printf("EulerPhi(%d) = %lld\n", 10, EulerPhi(10)); // 6 integers < 7 are relatively prime with prime number 7

    return 0;
}
