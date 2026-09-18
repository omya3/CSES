long long MOD = 1e9 + 7;
vector<long long> fused(1000001, 0);
vector<long long> separate(1000001, 0);

// Base cases
fused[1] = 1;
separate[1] = 1;

// Fill the table bottom-up
for (int i = 2; i <= 1000000; i++)
{
    fused[i] = (2 * fused[i - 1] + separate[i - 1]) % MOD;
    separate[i] = (fused[i - 1] + 4 * separate[i - 1]) % MOD;
}
