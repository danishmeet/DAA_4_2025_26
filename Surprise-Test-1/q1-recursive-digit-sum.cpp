int superDigit(string n, int k){
    long long sum = 0;
    for (char c : n) {
        sum+=c-'0';
    }
    sum *= k;
    while(sum >= 10) {
        long long temp = 0;
        while(sum > 0) {
            temp += sum % 10;
            sum /= 10;
        }
        sum = temp;
    }
    return sum;
}