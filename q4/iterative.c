
int maxSubArray(int* s, int ns)
{
    int t = 0;
    int max = s[0];
    for (int i = 0; i < ns; ++i) {
        if (t>0)
            t += s[i];
        else
            t = s[i];
        max = max > t ? max : t;
    }
    return max;
}
