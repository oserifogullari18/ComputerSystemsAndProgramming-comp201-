int foo2(int x, int y, int z){
    return x+y+z;
}
int foo1(int a1, int a2, int a3, int a4, int a5){
    return foo2(a1, a2*a3, a4+a5);
}
int foo(){
    int f = 1;
    int s = 2;
    int t = 3;
    int fo = 4;
    int fi = 5;
    return foo1(f, s, t, fo, fi);
}
//OZLEM SERIFOGULLARI