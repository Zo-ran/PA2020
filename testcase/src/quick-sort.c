#include"trap.h"

int main(){
    int n, target, min = 21211212, tail = 0, head = 0, sum = 0, judge = false, cnt = 0;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    cin >> target;
    int b[2 * n];
    for(int i = 0; i < n; i++){
        b[tail++] = a[i]; 
        sum += a[i];
        cnt++;
        while(sum >= target){
            judge = true;
            if(cnt < min)
                min = cnt;
            cnt--;
            sum -= a[head++];
        }
    }
    if(!judge)
        cout << 0 << endl;
    else
        cout << min << endl;
    return 0;
}