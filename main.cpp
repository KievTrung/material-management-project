#include <iostream>
#include <dos.h> // Sleep()
#include <stdio.h>
#include <ctime> // time()
#include <cstdlib> //rand(), srand()
#include "mylib.h"//gotoxy()
#include <limits.h> //INT_MAX
using namespace std;

/////KEYWORD//////
#define MAXNV 300
#define MAXVT 20
#define DEFAULT_ITEM 5
#define DEFAULT_COL 30
#define ON true
#define OFF false
#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define MODE_4 4
#define MODE_5 5
#define MODE_6 6
#define MODE_7 7
#define MODE_8 8
#define MODE_9 9
#define MODE_10 10
#define MODE_11 11
#define MODE_12 12
#define MODE_13 13
#define MODE_14 14
#define MODE_15 15
#define MODE_16 16
#define MODE_17 17

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define LIGHT_BLUE 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define LIGHTER_GRAY 7
#define GRAY 8
#define LIGHTER_BLUE 9
#define LIGHTER_GREEN 10
#define LIGHTEST_BLUE 11
#define LIGHTER_RED 12
#define LIGHTER_PURPLE 13
#define YELLOW 14
#define WHITE 15

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESCAPE 27
#define HORIZONTAL 205
#define VERTICAL 186
#define CTRL_A 1
///////////////////

///////MENU LIST//////////////////////////////////////cac menu thuc don co trong chuong trinh
const int item_main = 6;
char main_menu[item_main][DEFAULT_COL] = {"1. DANH SACH VAT TU ", "2. DANH SACH NHAN VIEN ", "3. TAO HOA DON ", "4. THONG KE ", "5. LOAD FILE   CREATE DEMO ", "   EXIT "};

const int item_modify = 4;
char modify_menu[item_modify][DEFAULT_COL] = {"ADD", "MODIFY", "DELETE", "EXIT"};

const int item_nvinfo = 3;
char nvinfo_menu[item_nvinfo][DEFAULT_COL] = {"HO VA TEN", "TEN", "GIOI TINH"};

const int item_save = 3;
char save_menu[item_save][DEFAULT_COL] = {"SAVE", "BACK", "DELETE"};

const int item_sex = 2;
char sex_menu[item_sex][DEFAULT_COL] = {"NAM", "NU"};

const int item_ttvt = 3;
char ttvt_menu[item_ttvt][DEFAULT_COL] = {"TEN VAT TU", "DON VI TINH", "SO LUONG TON"};

const int item_Fread = 2;
char Fread_menu[item_Fread][DEFAULT_COL] = {"LOAD FILE", "CREATE DEMO"};

const int item_cthd = 5;
char cthd_menu[item_cthd][DEFAULT_COL] = {"MA VT", "SO LUONG", "DON GIA", "VAT(%)", "CREATE DEMO CTHD"};

const int item_hd = 4;
char hd_menu[item_hd][DEFAULT_COL] = {"MA NHAN VIEN", "LOAI HD", "CHI TIET HOA DON", "IN HOA DON"};

const int item_thongke = 4;
char thongke_menu[item_thongke][DEFAULT_COL] = {"1. HOA DON ", "2. VAT TU ", "3. DOANH THU", "EXIT"};

//////////////////////////////////////////////////////


/////////////////////////STRUCT/////////////////////////////////////
struct VATTU {
    char mavt[10];
    char tenvt[20];
    char don_vi_tinh[5];
    int soluongton=0;
};
struct DSVATTU {
    int key;
    VATTU info;
    DSVATTU* left = NULL;
    DSVATTU* right = NULL;
};
typedef DSVATTU* VTPTR;

struct chitietHD {
    char mactvt[10];
    char tenctvt[20];
    int soluong;
    int dongia;
    float vat;
};
struct DS_CTHD {
    int n=0;
    unsigned int total = 0;
    chitietHD* cthd[MAXVT];
};

class date
{
public:
    int ngay;
    int thang;
    int nam;
    int gio;
    int phut;
    date (){ngay = 0; thang= 0; nam = 0; gio = 0; phut = 0;};
    date (int day, int month, int year){ngay = day; thang= month; nam = year; gio = 0; phut = 0;};
    date (const date& obj1){ gio = obj1.gio; phut = obj1.phut; ngay = obj1.ngay; thang = obj1.thang; nam = obj1.nam; };
    date& operator=(const date& rhs){
        this->ngay = rhs.ngay;
        this->thang = rhs.thang;
        this->nam = rhs.nam;
        this->gio = rhs.gio;
        this->phut = rhs.phut;
        return *this;
    };
    bool operator<= (const date& rhs){
        int temp = this->nam - rhs.nam;
        if(temp > 0) return false;
        else if(temp == 0)
        {
            temp = this->thang - rhs.thang;
            if(temp > 0) return false;
            else if(temp == 0)
            {
                temp = this->ngay - rhs.ngay;
                if(temp > 0) return false;
                else if(temp == 0)
                {
                    temp = this->gio - rhs.gio;
                    if(temp > 0) return false;
                    else if(temp == 0)
                    {
                        temp = this->phut - rhs.phut;
                        if(temp > 0) return false;
                    }
                }
            }
        }
        return true;
    }
    bool operator>= (const date& rhs){
        int temp = this->nam - rhs.nam;
        if(temp < 0) return false;
        else if(temp > 0) return true;
        else if(temp == 0)
        {
            temp = this->thang - rhs.thang;
            if(temp < 0) return false;
            else if(temp > 0) return true;
            else if(temp == 0)
            {
                temp = this->ngay - rhs.ngay;
                if(temp < 0) return false;
                else if(temp > 0) return true;
                else if(temp == 0)
                {
                    temp = this->gio - rhs.gio;
                    if(temp < 0) return false;
                    else if(temp > 0) return true;
                    else if(temp == 0)
                    {
                        temp = this->phut - rhs.phut;
                        if(temp < 0) return false;
                    }
                }
            }
        }
        return true;
    }
    bool operator> (const date& rhs){
        int temp = this->nam - rhs.nam;
        if(temp < 0) return false;
        else if(temp == 0)
        {
            temp = this->thang - rhs.thang;
            if(temp < 0) return false;
            else if(temp == 0)
            {
                temp = this->ngay - rhs.ngay;
                if(temp < 0) return false;
                else if(temp == 0)
                {
                    temp = this->gio - rhs.gio;
                    if(temp < 0) return false;
                    else if(temp == 0)
                    {
                        temp = this->phut - rhs.phut;
                        if(temp < 0 || temp == 0) return false;
                    }
                }
            }
        }
        return true;
    }
    bool operator< (const date& rhs){
        int temp = this->nam - rhs.nam;
        if(temp > 0) return false;
        else if(temp == 0)
        {
            temp = this->thang - rhs.thang;
            if(temp > 0) return false;
            else if(temp == 0)
            {
                temp = this->ngay - rhs.ngay;
                if(temp > 0) return false;
                else if(temp == 0)
                {
                    temp = this->gio - rhs.gio;
                    if(temp > 0) return false;
                    else if(temp == 0)
                    {
                        temp = this->phut - rhs.phut;
                        if(temp > 0 || temp == 0) return false;
                    }
                }
            }
        }
        return true;
    }
};

struct dshd {
    char soHD[20];
    date thoigian;
    char loai = NULL;
    DS_CTHD* ptr = NULL;
};
struct node_hd{
    dshd info;
    node_hd* next = NULL;
};
typedef node_hd* PTRHD;

struct NHANVIEN{
    char state;//nếu thông tin trong field bị thay đổi thì trạng thái sẽ thay đổi
    int manv;
    char hoten[30];
    char ten[10];
    char gioitinh = '0';
    PTRHD first = NULL;
};
struct Listnv {
    int n = 0;
    NHANVIEN* nvnode[MAXNV];
};

struct DTVT{//h
    int madtvt;
    char tendtvt[20];
    unsigned int doanhthu = 0;
};
struct listvt{//h
    DTVT info;
    listvt* next = NULL;
};

struct knode{
    int key;
    char tenvt[20];
    bool flag;
    knode* next = NULL;
};
typedef knode* KPTR;
////////////////////////////////////////////////////////////////////

void vatTuInfo(VTPTR &root, KPTR &keyArr);
void addvatTu(VTPTR &root, KPTR &keyArr);
void VT_Save_Procedure(VTPTR &root, VATTU &info, KPTR &keyArr);
void modifyVattu(VTPTR &root, KPTR &keyArr);
void deleteVattu(VTPTR &root, KPTR &keyArr);

void nhanVienInfo(Listnv &dsnv);
void addNhanvien(Listnv &dsnv);
void NV_Save_Procedure(Listnv& dsnv, NHANVIEN* &info);
void modifyNhanvien(Listnv &dsnv);
void deleteNhanvien(Listnv &dsnv);

int loadFile_creDemo(Listnv &dsnv, VTPTR &root, KPTR &keyArr);

///////////////////////FUCNTION DECLARATION/////////////////////////
int soVT(KPTR &head);
int* convert_keyArr(KPTR &keyArr, bool modify, int &soKey);
int power(int coso, int mu);
bool checkfield(char* arr, int kytu_minimum);
bool checkEmpty(char &head);
bool checkTenvt(KPTR &head, char *info);
VTPTR newNode(int key, VATTU info);
knode initKey(int k, char* tenvt, bool setFlag);
bool insert_Key(KPTR &head, knode info);
void delete_Key(KPTR &head, int k);
KPTR MergeSort(KPTR &head);
KPTR mergeList(KPTR &headA, KPTR &headB);
int keyGen(KPTR &head, char *tenvt, bool setFlag);
VTPTR Rotate_Left(VTPTR root);
VTPTR Rotate_Right(VTPTR root);
int height(VTPTR p);
int getbf(VTPTR p);
VTPTR insertTree(VTPTR &p, int k, VATTU info);
VTPTR removeNode(VTPTR &p, int k);
VATTU searchTree(const VTPTR &root, int k);
void infokeyModify(KPTR &head, int k, char* tenvt);
void infovtModify(VTPTR &p, int k, VATTU inf);//ham thay doi thong tin trong tree dua tren bien inf
void vtDisplay(VATTU inf, int col, int row);
void dsvtDisplay(VTPTR &p, KPTR &head, int col, int row, bool dis_mavt);
void remove_case_3(VTPTR &r);
void deleteVT(VTPTR &p, KPTR &keyArr, int k);
bool delmultiVT(VTPTR &p, KPTR &keyArr, int* flag, int item);

int strComp_v2(NHANVIEN left, NHANVIEN right);
void relocNV(Listnv &dsnv);
void dsnvDisplay(Listnv &ds, int col, int row, bool manvdis);
int setVal(int *manv, Listnv &ds);
int nvDisplay(NHANVIEN info);
int searchManv(Listnv &ds, int code);
void deleteNV(Listnv &ds, int index);
bool delmultiNV(Listnv& ds, int *flag, int MAX);

date dateInfo();
void mahdGen_sub(int MAX, int val, char *a, int a_index);
void mahdGen(char *maHD, int manv, date obj, char loaiHD, int soCTHD);
void addHD(dshd val, Listnv &dsnv, int nvindex);
int getSLT(const VTPTR &root, int k);
void putSTL(VTPTR &root, int k, int SLT);
void updateVT(VTPTR &dsvt, DS_CTHD cthd, char loaiHD);
int dshdDisplay(Listnv &dsnv, int nvindex, int col, int row);
void hdInfo(Listnv &dsnv, VTPTR &dsvt, KPTR &keyArr);
bool inDSHD(Listnv &dsnv, int nvindex, int *flag, int MAX);
char* numConvert_v2(int num);
void appArr(char *arr1, char *arr2, char *arr3);
void inHD(NHANVIEN nv, dshd info);
bool checkVT(KPTR &keyArr, int key);
void cthdDefault(chitietHD &obj);
void cthdDisplay(DS_CTHD obj, int col, int row, bool mavt_display);
void cthdInfo(VTPTR dsvt, KPTR &keyArr, char loaiHD, DS_CTHD* dscthd);
int totalCTHD(chitietHD val);

int timeInterval(date &timeA, date &timeB, int col, int row);
void thongKe(Listnv &dsnv);
void insertAfter(PTRHD &head, dshd val);
int thongkeHD(Listnv &dsnv, date timeA, date timeB, int col, int row);
void insertLast_listvt(listvt* &head, DTVT val);
void extractListvt(listvt* &head1, listvt* &head2, int val);
void find_add_MaxDT(listvt* &thongke_dtvt, listvt* &top10);
int thongkeVT(Listnv &dsnv, date timeA, date timeB, int col, int row);
int thongkeDT(Listnv &dsnv, int year, int col, int row);

void Normal();
void highlight();
void highlight2();
void highlight3();
int MENU_DONG_NGANG(char menu[DEFAULT_ITEM][DEFAULT_COL], int item, int col, int row, int gap, bool up_down, bool escape, int color, int bgcolor, int choose = 0);
int MENU_DONG_DOC(char menu[DEFAULT_ITEM][DEFAULT_COL], int item, int col, int row, bool left_on, bool right_on, int gap, int color, int bgcolor, int choose=0); //ham tao menu doc
int MENU_DONG_DOC_FOR_NUMBER(int* menu, int item, int col, int row, int gap, int color=WHITE, int bgcolor=RED, int choose=0);
int* MENU_DONG_DOC_FOR_NUMBER_v2(int* menu, int item, int col, int row, int color, int bgcolor);
void random_word(char* arr, int MAX);
void POP_UP(int col, int row, int col_back, int row_back, int num, int warn_switch, int minimum = 0); // ham output canh bao
void preFram(int fram, bool display = OFF);
bool exitpop(int col, int row, int asked=0);
void FRAME(int color, int col, int row, int height, int width); // ham tao khung color
void DELCOLOR(int col, int row, int width, int height);
void resize_window(int x, int y, int width, int height); // ham dieu chinh kich thuoc window
void namefilter(char* arr);
int nhapSo(int MAX, int col, int row);
void nhapChu(char* arr, int MAX, int col, int row, bool swit);
void numConvert(int num, char* arr, int MAX);// ham chuyen kieu int sang char array theo format
int numConvert_reverse(char *arr);
void instruct(int col, int row, const char* menu);
int strComp(char *left, char *right);
int arrCopy(char *arr1, int a1_index, char *arr2);
void arrCopy_v2(char *arr1, char *arr2, int maxa2);

void saveInfoVT(VTPTR &root, KPTR &keyArr);//lưu tất cả thông tin vật tư trong tree
void loadFileVT(VTPTR &root, KPTR &keyArr);//hàm load file
void filenameCre(int manv, char* fname);
void saveInfoNV(Listnv &ds);
int getsoCTHD(char *soHD);
void loadFileNV(Listnv &ds);

DS_CTHD cthdDemo(VTPTR &dsvt, KPTR &keyArr);
void dshdDemo(Listnv &dsnv, VTPTR &dsvt, KPTR &keyArr, int nvindex);
void creDemo(VTPTR &dsvt, Listnv &ds, KPTR &keyArr);
////////////////////////////////////////////////////////////////////

VTPTR rp; //con trỏ dùng cho chức năng xóa node trong tree

date now = dateInfo();//Khởi tạo biến hỗ trợ tạo demo

int main()
{
    srand(time(NULL));//random

    Listnv dsnv;//danh sach nv
    KPTR key = NULL; //danh sach key vat tu
    VTPTR root = NULL;//danh sach vat tu

    bool loop = ON;
    int choose = 0; //biến dùng để lưu thực đơn vừa được chọn
    int opt;
    do
    {
        preFram(MODE_0);
        opt = MENU_DONG_DOC(main_menu, item_main, 0, 7, OFF, OFF, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1: // lua chon so 1
            vatTuInfo(root, key);
            choose = --opt;
            break;
        case 2: // lua chon so 2
            nhanVienInfo(dsnv);
            choose = --opt;
            break;
        case 3: //TAO HOA DON
            if(dsnv.n != 0 && root != NULL)//phai co nhan vien moi duoc dung chuc nang nay
                hdInfo(dsnv, root, key);
            if(dsnv.n == 0)
                POP_UP(13, 18, 13, 19, 0, MODE_15);
            if(root == NULL)
                POP_UP(13, 18, 13, 19, 0, MODE_14);
            choose = --opt;
            break;
        case 4: //lua chon so 4
            if(dsnv.n != 0 && root != NULL)//phai co nhan vien moi duoc dung chuc nang nay
                thongKe(dsnv);
            if(dsnv.n == 0)
                POP_UP(13, 18, 13, 19, 0, MODE_15);
            if(root == NULL)
                POP_UP(13, 18, 13, 19, 0, MODE_14);
            choose = --opt;
            break;
        case 5://load file or create demo
            choose = loadFile_creDemo(dsnv, root, key);
            break;
        case 6: // lua chon exit
            if(dsnv.n != 0 && root != NULL)
                if(exitpop(13, 18, MODE_1))
                {
                    saveInfoVT(root, key);
                    saveInfoNV(dsnv);
                    POP_UP(13, 18, 13, 19, 0, MODE_17);
                }
            loop = !(exitpop(13, 18));
            choose = --opt;
            break;
        }
    }
    while(loop);
    clrscr();
    return 0;
}

///////////////////////FUCNTION DEFINITION//////////////////////////
void vatTuInfo(VTPTR &root, KPTR &keyArr)//1
{
    bool display = ON;//biến cho phép danh sách vật tư đc hoặc ko hiển thị
    bool loop1 = ON;
    int opt1;
    int choose0 = 0;//luu gia tri lua chon
    do
    {
        preFram(MODE_1, display);
        instruct(70, 6, "MENU");
        if(root != NULL && display) dsvtDisplay(root, keyArr, 10, 17, ON);//hien thi danh sach vat tu neu trong tree có vật tư
        opt1 = MENU_DONG_DOC(modify_menu, item_modify, 1, 5, OFF, OFF, 2, WHITE, RED, choose0);//tao menu add, modify, delete
        switch(opt1)
        {
        case 1://ADD
            display = OFF;//mặc định tắt nếu có thay đổi mới bật
            addvatTu(root, keyArr);
            choose0 = --opt1;
            break;
        case 2://MODIFY
            display = OFF;
            if(root != NULL)// chỉ dùng đc modify khi tree có node tức là chỉ khi có vật tư mới đc chỉnh sửa
            {
                display = ON;
                modifyVattu(root, keyArr);
            }
            else POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_3);// hiển thị cảnh báo chưa có vật tư nào trong tree
            choose0 = --opt1;
            break;
        case 3://DELETE
            display = OFF;
            if(root != NULL)//chỉ thực hiện khi trong tree có node
            {
                display = ON;//khi vào trong phần code này->có thể dsvt đã bị thay đổi hoặc ko nên
                deleteVattu(root, keyArr);
            }
            else POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_3);// hiển thị cảnh báo chưa có vật tư nào trong tree
            choose0 = --opt1;
            break;
        case 4://EXIT
            loop1 = OFF;
            clrscr();
            break;
        }
    }
    while(loop1);
}

void addvatTu(VTPTR &root, KPTR &keyArr)
{
    preFram(MODE_3);
    instruct(70, 6, "INFO");
    VATTU temp_add;//tao bien temp de luu thong tin vat tu
    bool loop = ON;
    int opt;
    int choose = 0;//luu gia tri lua chon
    do
    {
        preFram(MODE_3);//tao khung mac dinh cho menu
        opt = MENU_DONG_DOC(ttvt_menu, item_ttvt, 10+1, 5+1, OFF, ON, 2, WHITE, RED, choose);//tao menu nhap thong tin vat tu
        switch(opt)
        {
        case 1://NHAP TEN VT
            DELCOLOR(10+15, 5+1, 30, 1);
            while(true)
            {
                nhapChu(temp_add.tenvt, 20, 10+15, 5+1, OFF);
                if(checkfield(temp_add.tenvt, 3))
                {
                    if(checkTenvt(keyArr, temp_add.tenvt))
                    {
                        namefilter(temp_add.tenvt);
                        break;
                    }
                }
                else
                {
                    POP_UP(10+15, 5+9, 10+15, 5+1, 30, MODE_1, 3);
                    break;
                }
            }
            choose = --opt;
            break;
        case 2://NHAP DON VI TINH
            DELCOLOR(10+15, 5+3, 10, 1);
            while(true)
            {
                nhapChu(temp_add.don_vi_tinh, 5, 10+15, 5+3, ON);
                if(checkfield(temp_add.don_vi_tinh, 2))
                {
                    namefilter(temp_add.don_vi_tinh);
                    break;
                }
                else
                {
                    POP_UP(10+15, 5+9, 10+15, 5+3, 10, MODE_1, 2);
                    break;
                }
            }
            choose = --opt;
            break;
        case 3://NHAP SO LUONG TON
            {
                DELCOLOR(10+15, 5+5, 30, 1);
                temp_add.soluongton = nhapSo(10, 10+15, 5+5);
            }
            choose = --opt;
            break;
        case 0://SAVE OR EXIT
            {
                int opt2 = MENU_DONG_DOC(save_menu, 2, 62, 5, ON, OFF, 2, WHITE, RED);/*save process*/
                switch(opt2)
                {
                case 1:
                    if(checkEmpty(temp_add.tenvt[0]) || checkEmpty(temp_add.don_vi_tinh[0]))
                        POP_UP(10+15, 5+9, 10+30, 5+9, 0, MODE_5);
                    else if(exitpop(84, 7, 2))
                       VT_Save_Procedure(root, temp_add, keyArr);
                    break;
                case 2:
                    loop = OFF;
                    break;
                case -1:
                    break;
                }
            }
            break;
        }
    }
    while(loop);
}

void VT_Save_Procedure(VTPTR &root, VATTU &info, KPTR &keyArr)
{
    int k = keyGen(keyArr, info.tenvt, ON);//tao khoa va luu trong chuoi keyArr
    numConvert(k, info.mavt, 10);//chuyển khóa k sang định dạng char đưa vào temp_add.mavt
    root = insertTree(root, k, info);//đẩy thông tin vào tree dựa trên khóa k
    DELCOLOR(10+15, 5+1, 30, 1);//
    DELCOLOR(10+15, 5+3, 10, 1);//xóa các ký tự hiển thị nhập cũ
    DELCOLOR(10+15, 5+5, 30, 1);//
    dsvtDisplay(root, keyArr, 10, 17, ON);//hiển thị danh sách
    gotoxy(0, 0); //tự động đi lên đầu
}

void modifyVattu(VTPTR &root, KPTR &keyArr)
{
    preFram(MODE_4);
    instruct(70, 6, "MODIFY");//Hiển thị hướng dẫn sử dụng
    bool swit = OFF;
    int num; //bien luu giu so luong mavt
    VATTU temp_mod;//biến tạm để chứa thong tin can chinh sua
    dsvtDisplay(root, keyArr, 10, 17, OFF); //hien thi danh sach vat tu
    int* maVT = convert_keyArr(keyArr, ON, num);
    int key_return = MENU_DONG_DOC_FOR_NUMBER(maVT, num, 13, 19, 1);//đếm số phần tử vat tu có trong chuỗi maVT dùng hàm modItem
                                                                    //và hiển thị menu key cua các vật tư muốn chinh sua bằng menu động
    instruct(70, 6, "INFO");
    if(key_return == -1) return;//nếu ko modify nữa thì thoát ra ngoài (ESCAPE)
    temp_mod = searchTree(root, key_return);//tim key trong tree va đưa thong tin vat tu vao trong bien temp_mod
    vtDisplay(temp_mod, 10+15, 5); //hiển thị thông tin vật tư cần chỉnh sửa thông qua biến temp_mod                        {

    bool loop = ON;
    int opt;
    int choose = 0;
    do
    {
        if(root == NULL) break;
        else if(swit)//đoạn code ở trên thực thi rồi thì dưới ko thực thi nữa
        {
            instruct(70, 6, "MODIFY");
            dsvtDisplay(root, keyArr, 10, 17, OFF); //hien thi danh sach vat tu
            maVT = convert_keyArr(keyArr, ON, num);
            key_return = MENU_DONG_DOC_FOR_NUMBER(maVT, num, 13, 19, 1);
            instruct(70, 6, "INFO");
            if(key_return == -1) break;//nếu ko chinh sua nữa thì thoát ra ngoài (ESCAPE)
            temp_mod = searchTree(root, key_return);
            vtDisplay(temp_mod, 10+15, 5);
            swit = OFF;
        }
        int opt = MENU_DONG_DOC(ttvt_menu, item_ttvt, 10+1, 5+1, OFF, ON, 2, WHITE, RED, choose);//tạo menu chỉnh sửa cho biến vật tư temp_mod
        switch(opt)
        {
        case 1:
            if(exitpop(84, 7, MODE_3))//hỏi xem bạn có chắc chắn muốn chỉnh sửa
            {
                DELCOLOR(10+15, 5+1, 30, 1);
                while(true)
                {
                    nhapChu(temp_mod.tenvt, 20, 10+15, 5+1, OFF);
                    if(checkfield(temp_mod.tenvt, 3) && checkTenvt(keyArr, temp_mod.tenvt))
                    {
                        namefilter(temp_mod.tenvt);
                        break;
                    }
                    else
                    {
                        POP_UP(10+15, 5+9, 10+15, 5+1, 30, MODE_1, 3);
                        break;
                    }
                }
            }
            choose = --opt;
        break;
        case 2:
            if(exitpop(84, 7, MODE_3))//hỏi xem bạn có chắc chắn muốn chỉnh sửa
            {
                DELCOLOR(10+15, 5+3, 10, 1);
                while(true)
                {
                    nhapChu(temp_mod.don_vi_tinh, 5, 10+15, 5+3, ON);
                    if(checkfield(temp_mod.don_vi_tinh, 2))
                    {
                        namefilter(temp_mod.don_vi_tinh);
                        break;
                    }
                    else
                    {
                        POP_UP(10+15, 5+9, 10+15, 5+3, 30, MODE_1, 2);
                        break;
                    }
                }
            }
            choose = --opt;
        break;
        case 3:
            if(exitpop(84, 7, MODE_3))//hỏi xem bạn có chắc chắn muốn chỉnh sửa
            {
                DELCOLOR(10+15, 5+5, 30, 1);
                temp_mod.soluongton = nhapSo(10, 10+15, 5+5);
            }
            choose = --opt;
        break;
        case 0:// option saving or exiting
            {
                int opt2 = MENU_DONG_DOC(save_menu, item_save, 62, 5, ON, OFF, 2, WHITE, RED);
                switch(opt2)
                {
                case 1://lựa chọn save node
                {
                    if(checkEmpty(temp_mod.tenvt[0]) || checkEmpty(temp_mod.don_vi_tinh[0]))
                            POP_UP(10+15, 5+9, 10+30, 5+9, 0, MODE_5);
                    else if(exitpop(84, 7, MODE_2))
                    {
                        infokeyModify(keyArr, key_return, temp_mod.tenvt);
                        infovtModify(root, key_return, temp_mod);
                        keyArr = MergeSort(keyArr);//sắp xếp lại chuoi link listed keyArr
                        DELCOLOR(10+15, 5+1, 30, 1);
                        DELCOLOR(10+15, 5+3, 10, 1);
                        DELCOLOR(10+15, 5+5, 30, 1);
                        swit = ON;
                    }
                }
                //..check to see if it valid or not
                break;
                case 2://lựa chọn xóa node
                    loop= OFF;
                break;
                case 3:
                    if(exitpop(84, 7, MODE_3))
                    {
                        DELCOLOR(10+15, 5+1, 30, 1);
                        DELCOLOR(10+15, 5+3, 10, 1);
                        DELCOLOR(10+15, 5+5, 30, 1);
                        deleteVT(root, keyArr, key_return);
                        swit = ON;
                    }
                break;
                case -1:
                break;
                }
            }
            break;
        }
    }
    while(loop);
}

void deleteVattu(VTPTR &root, KPTR &keyArr)
{
    while(true)
    {
        preFram(MODE_10);
        dsvtDisplay(root, keyArr, 10, 8, OFF);
        gotoxy(0, 0);/*đi lên đầu*/
        int num;
        int *mavt = convert_keyArr(keyArr, OFF, num);
        if(num == 0) break;
        else
        {
            int *flag = MENU_DONG_DOC_FOR_NUMBER_v2(mavt, num, 13, 10, WHITE, RED);
            if(delmultiVT(root, keyArr, flag, num))
            {
                delete(flag);
                break;
            }
        }
    }
    clrscr();
}



void nhanVienInfo(Listnv &dsnv)//2
{
    bool loop2 = ON;
    int opt2, choose1=0; /*menu thuc don cua lua chon thu 2*/
    do
    {
        preFram(MODE_2);
        preFram(MODE_3);
        instruct(71, 6, "MENU");
        if(dsnv.n != 0) dsnvDisplay(dsnv, 10, 17, ON);
        opt2 = MENU_DONG_DOC(modify_menu, item_modify, 1, 5, OFF, OFF, 2, WHITE, RED, choose1);
        switch(opt2)
        {
        case 1: //ADD
            if(dsnv.n != MAXNV)
                addNhanvien(dsnv);
            else POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_7);// hiển thị cảnh báo đã tối đa nhân viên ko đc thêm nữa
            choose1=--opt2;
            break;
        case 2://MODIFY
            if(dsnv.n != 0)
                modifyNhanvien(dsnv);
            else POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_3);// hiển thị cảnh báo chưa có nhân viên nào trong danh sách
            choose1=--opt2;
            break;
        case 3://DELETE
            if(dsnv.n != 0)//chỉ thực hiện khi trong tree có node
                deleteNhanvien(dsnv);
            else POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_3);// hiển thị cảnh báo chưa có nhân viên nào trong danh sách
            choose1=--opt2;
            break;
        case 4://EXIT
            loop2 = OFF;
            clrscr();
            break;
        }
    }
    while(loop2);
}

void addNhanvien(Listnv &dsnv)
{
    NHANVIEN* temp = new NHANVIEN;//tạo biến tạm để lưu thông tin nhân viên vừa nhập
    bool loop = ON;
    int opt, choose=0;
    do
    {
        instruct(71, 6, "INFO");
        if(dsnv.n == MAXNV)// check xem sau khi thêm vt thì dsvt đã đầy chưa
        {
            POP_UP(10+15, 5+9, 10+40, 5+9, 0, MODE_7);// hiển thị cảnh báo đã tối đa vật tư ko đc thêm nữa
            break;
        }
        preFram(MODE_3);
        opt = MENU_DONG_DOC(nvinfo_menu, item_nvinfo, 11, 6, OFF, ON, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1://TYPE hoten
            DELCOLOR(10+11, 5+1, 30, 1);
            while(true)
            {
                nhapChu(temp->hoten, 30, 10+11, 5+1, OFF);
                if(checkfield(temp->hoten, 10))//MIN_WORD
                {
                    namefilter(temp->hoten);
                    break;
                }
                else
                {
                    POP_UP(10+11, 5+9, 10+11, 5+1, 30, MODE_1, 10);
                    break;
                }
            }
            choose = --opt;
        break;
        case 2://TYPE ten
            DELCOLOR(10+11, 5+3, 30, 1);
            while(true)
            {
                nhapChu(temp->ten, 10, 10+11, 5+3, OFF);
                if(checkfield(temp->ten, 5))//MIN_WORD
                {
                    namefilter(temp->ten);
                    break;
                }
                else
                {
                    POP_UP(10+11, 5+9, 10+11, 5+3, 30, MODE_1, 5);
                    break;
                }
            }
            choose = --opt;
        break;
        case 3://CHOOSE gioitinh
            {
                int opt2_1_3 = MENU_DONG_NGANG(sex_menu, item_sex, 10+13, 5+5, 12, OFF, ON, WHITE, RED);
                switch(opt2_1_3)
                {
                case 1:
                    temp->gioitinh = '2';//nam
                    break;
                case 2:
                    temp->gioitinh = '1';//nu
                    break;
                }
            }
            choose = --opt;
        break;
        case 0://SAVE OR EXIT
            {
                int opt2 = MENU_DONG_DOC(save_menu, 2, 62, 5, ON, OFF, 2, BLACK, LIGHTER_GRAY);
                switch(opt2)
                {
                case 1:/*save process*/
                    if(checkEmpty(temp->hoten[0]) || checkEmpty(temp->ten[0]) || temp->gioitinh == '0')
                        POP_UP(10+11, 5+9, 10+30, 5+9, 0, MODE_5);
                    else if(exitpop(85, 5, 2))
                        NV_Save_Procedure(dsnv, temp);
                break;
                case 2:
                    delete(temp);
                    loop = OFF;
                break;
                case -1:
                    break;
                }
            }
            choose = opt;
            break;
        }
    }
    while(loop);
}

void NV_Save_Procedure(Listnv& dsnv, NHANVIEN* &info)
{
    info->manv = dsnv.n+1;//tao ma nhan vien
    dsnv.nvnode[dsnv.n] = info;
    info->state = '1'; //
    dsnv.n++;
    info = new NHANVIEN;
    relocNV(dsnv);//sắp xếp lại danh sách nhân viên
    DELCOLOR(10+11, 5+1, 30, 1);
    DELCOLOR(10+11, 5+3, 30, 1);
    gotoxy(10+13, 5+5);cout << sex_menu[0];
    gotoxy(10+13+12, 5+5);cout << sex_menu[1];
    dsnvDisplay(dsnv, 10, 17, ON);
}

void modifyNhanvien(Listnv &dsnv)
{
    preFram(MODE_4);
    bool swit = OFF;
    int maNV[dsnv.n];//tạo chuỗi lưu mã nv
    int slnv = setVal(maNV, dsnv);//set giá trị cho chuỗi maNV qua truy cập chuỗi dsnv và trả về số lượng nv
    dsnvDisplay(dsnv, 10, 17, OFF);//hiển thị danh sách nhân viên
    instruct(71, 6, "INFO");
    int manv_return = MENU_DONG_DOC_FOR_NUMBER(maNV, slnv, 15, 19, 1, WHITE, RED);//tạo menu mã dựa trên chuỗi maNV và trả về mã cần chỉnh sửa
    instruct(71, 6, "MENU");
    if(manv_return == -1) return;//nếu ko modify nữa thì thoát ra ngoài (ESCAPE)
    int index = searchManv(dsnv, manv_return);
    NHANVIEN temp = *(dsnv.nvnode[index]);
    nvDisplay(temp);//hiển thị thông tin nv
    bool loop = ON;
    int opt;
    int choose = 0;
    do
    {
        if(dsnv.n == 0) break;
        else if(swit)
        {
            slnv = setVal(maNV, dsnv);//set giá trị cho chuỗi maNV qua truy cập chuỗi dsnv và trả về số lượng nv
            dsnvDisplay(dsnv, 10, 17, OFF);//hiển thị danh sách nhân viên
            instruct(71, 6, "INFO");
            manv_return = MENU_DONG_DOC_FOR_NUMBER(maNV, slnv, 15, 19, 1, WHITE, RED);//tạo menu mã dựa trên chuỗi maNV và trả về mã cần chỉnh sửa
            instruct(71, 6, "MENU");
            if(manv_return == -1) break;//nếu ko modify nữa thì thoát ra ngoài (ESCAPE)
            index = searchManv(dsnv, manv_return);
            temp = *(dsnv.nvnode[index]);
            nvDisplay(temp);//hiển thị thông tin nv
            swit = OFF;
        }
        opt = MENU_DONG_DOC(nvinfo_menu, item_nvinfo, 11, 6, OFF, ON, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1://TYPE hoten
            DELCOLOR(10+11, 5+1, 30, 1);
            while(true)
            {
                nhapChu(temp.hoten, 30, 10+11, 5+1, OFF);
                if(checkfield(temp.hoten, 5))//MIN_WORD
                {
                    namefilter(temp.hoten);
                    break;
                }
                else
                {
                    POP_UP(10+11, 5+9, 10+11, 5+1, 30, MODE_1, 10);
                    break;
                }
            }
            choose = --opt;
        break;
        case 2://TYPE ten
            DELCOLOR(10+11, 5+3, 30, 1);
            while(true)
            {
                nhapChu(temp.ten, 10, 10+11, 5+3, OFF);
                if(checkfield(temp.ten, 2))//MIN_WORD
                {
                    namefilter(temp.ten);
                    break;
                }
                else
                {
                    POP_UP(10+11, 5+9, 10+11, 5+3, 30, MODE_1, 5);
                    break;
                }
            }
            choose = --opt;
        break;
        case 3://CHOOSE gioitinh
            {
                int opt2_2_3 = MENU_DONG_NGANG(sex_menu, item_sex, 10+13, 5+5, 12, OFF, ON, WHITE, RED);
                switch(opt2_2_3)
                {
                case 1:
                    temp.gioitinh = '2';//nam
                    break;
                case 2:
                    temp.gioitinh = '1';//nu
                    break;
                }
            }
            choose = --opt;
        break;
        case 0://SAVE OR EXIT
            {
                int opt2 = MENU_DONG_DOC(save_menu, 3, 62, 5, ON, OFF, 2, BLACK, LIGHTER_GRAY);
                switch(opt2)
                {
                case 1://SAVE
                    if(checkEmpty(temp.hoten[0]) || checkEmpty(temp.ten[0]))
                    {
                        POP_UP(10+11, 5+9, 10+30, 5+9, 0, MODE_5);
                        break;
                    }
                    if(exitpop(85, 5, 2))
                    {
                        temp.state = '1';
                        *(dsnv.nvnode[index]) = temp;
                        relocNV(dsnv);//sắp xếp lại danh sách nhân viên
                        DELCOLOR(10+11, 5+1, 30, 1);
                        DELCOLOR(10+11, 5+3, 30, 1);
                        gotoxy(10+13, 5+5);cout << sex_menu[0];
                        gotoxy(10+13+12, 5+5);cout << sex_menu[1];
                        swit = ON;
                    }
                    break;
                case 2://EXIT
                    loop = OFF;
                    break;
                case 3://DELETE 1 nv
                    if(exitpop(85, 5, 2))
                    {
                        deleteNV(dsnv, index);
                        swit = ON;
                    }
                    break;
                case -1://BACK
                    break;
                }
            }
            choose = opt;
            break;
        }
    }
    while(loop);
}

void deleteNhanvien(Listnv &dsnv)
{
    while(true)
    {
        preFram(MODE_11);
        instruct(82, 10, "DELETE");
        dsnvDisplay(dsnv, 10, 8, OFF);
        gotoxy(0, 0);/*đi lên đầu*/
        int maNV[dsnv.n];//tạo chuỗi lưu mã nv
        if(setVal(maNV, dsnv) == 0) break;//set giá trị cho chuỗi maNV qua truy cập chuỗi dsnv
        else
        {
            int *flag = MENU_DONG_DOC_FOR_NUMBER_v2(maNV, dsnv.n, 14, 10, WHITE, RED);
            if(delmultiNV(dsnv, flag, dsnv.n))
            {
                delete(flag);
                break;
            }
        }
    }
    clrscr();
}

void thongKe(Listnv &dsnv)
{
    date timeA, timeB;
    bool loop = ON;
    int opt, choose = 0, val, num = 0;
    do
    {
        preFram(MODE_6);
        instruct(2, 14, "TK");
        opt = MENU_DONG_DOC(thongke_menu, item_thongke, 1, 5, OFF, OFF, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1://thong ke hoa don
            preFram(MODE_6);
            preFram(MODE_7);
            instruct(2, 14, "TK");
            while(true)
            {
                val = timeInterval(timeA, timeB, 35, 6);
                if(val == -1) break;
                DELCOLOR(25, 8, 100, 2+num);
                num = thongkeHD(dsnv, timeA, timeB, 25, 8);
            }
            num = 0;
            choose = --opt;
            break;
        case 2:
            preFram(MODE_6);
            preFram(MODE_8);
            instruct(2, 14, "TK");
            while(true)
            {
                val = timeInterval(timeA, timeB, 35, 6);
                if(val == -1) break;
                DELCOLOR(30, 9, 40, 2+num);
                num = thongkeVT(dsnv, timeA, timeB, 30, 9);
            }
            num = 0;
            choose = --opt;
            break;
        case 3:
            preFram(MODE_6);
            preFram(MODE_9);
            instruct(2, 14, "ENTER");
            while(true)
            {
                gotoxy(30, 5);
                gotoxy(65, 5); highlight3(); cout << "VUI LONG NHAP"; Normal();
                int nam = nhapSo(4, 58, 5);
                if(nam == 0) break;
                DELCOLOR(35, 7, 21, 2+num);
                num = thongkeDT(dsnv, nam, 35, 7);
            }
            num = 0;
            choose = --opt;
            break;
        case 4:
            loop = OFF;
            break;
        }
    }
    while(loop);
}

int loadFile_creDemo(Listnv &dsnv, VTPTR &root, KPTR &keyArr)//5
{
    bool loop = ON;
    int opt;
    do
    {
        opt = MENU_DONG_NGANG(Fread_menu, item_Fread, 3, 15, 12, OFF, ON, WHITE, RED);
        switch(opt)
        {
        case 1:
            if(exitpop(13, 18, MODE_3))
            {
                loadFileVT(root, keyArr);
                loadFileNV(dsnv);
            }
            break;
        case 2:
            if(exitpop(13, 18, MODE_3))
                creDemo(root, dsnv, keyArr);
            break;
        case -1://down
            return 5;
        case 0://up
            return 3;
        }
    }
    while(loop);
}

////////////////////////////////////////////////////////////////////

///////////////////////FOR VAT TU///////////////////////////////////
knode initKey(int k, char* tenvt, bool setflag)//khoi tao cho bien key
{
    knode newkey;
    newkey.key = k;
    newkey.flag = setflag;
    arrCopy_v2(newkey.tenvt, tenvt, 20);
    return newkey;
}

bool insert_Key(KPTR &head, knode info)
{
    KPTR newkey = new knode{info};

    KPTR p = head;
    if(p == NULL)
    {
        head = newkey;
        return false;
    }
    for(; ; p = p->next)
    {
        if(p->key == info.key)//duplicate
        {
            delete(newkey);
            return true;
        }
        if(p->next == NULL)//insert last
        {
            p->next = newkey;
            return false;
        }
    }
}

void delete_Key(KPTR &head, int k)
{
    KPTR p = head, q;
    if(p->key == k)//delete first
    {
        q = p;
        head = p->next;
        delete(q);
        return;
    }
    for(;;p = p->next)
    {
        if(p->next == NULL)//delete last
        {
            q->next = NULL;
            delete(p);
            return;
        }
        if(p->key == k)//delete after
        {
            q->next = p->next;
            //p = q;
            delete(p);
            return;
        }
        q = p;
    }
}

int keyGen(KPTR &head, char* tenvt, bool setFlag) // ham sinh ra key cho binary tree
{
    int key;
    bool duplicate = true;
    while(duplicate)
    {
        key = rand()%(INT_MAX-1) + 1;
        duplicate = insert_Key(head, initKey(key, tenvt, setFlag));
    }
    head = MergeSort(head);
    return key;
}

bool checkfield(char* arr, int kytu_minimum)//ham check xem co du kytu_minimum trong chuoi
{
    int j=0;
    for(int i=0; arr[i]!=NULL; i++)
        if(arr[i] != ' ')
            ++j;
    if(j >= kytu_minimum)
        return true;
    return false;
}

bool checkEmpty(char &head)//ham check cem trong array co rong hay khong
{
    if(head==NULL)
        return true;
    else
        return false;
}

bool checkTenvt(KPTR &head, char *info)//hàm dựa vào hàm strComp check xem 2 chuỗi có trùng nhau ko nếu có thì trả về false và thông báo
{
    for(KPTR p = head; p != NULL; p = p->next)
    {
        if(strComp(info, p->tenvt) == 0)
        {
            gotoxy(10, 5+9);
            SetColor(YELLOW);
            SetBGColor(RED);
            cout << "\aDUPLICATE AT maVT: "<< p->key<<", tenVT: " <<p->tenvt <<". PLEASE RETYPE";
            getch();
            DELCOLOR(10, 5+9, 56, 1);
            DELCOLOR(10+15, 5+1, 20, 1);
            return false;
        }
    }
    return true;
}

int height(VTPTR p)
{
    if(p == NULL)
        return -1;
    else
    {
        int lh = height(p->left);
        int rh = height(p->right);
        if(lh > rh)
            return lh+1;
        else
            return rh+1;
    }
}

int getbf(VTPTR p)
{
    if(p == NULL)
        return -1;
    else
        return height(p->left) - height(p->right);
}

VTPTR newNode(int key, VATTU info)
{
    VTPTR n = new DSVATTU;
    n->info = info;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

VTPTR Rotate_Left(VTPTR root)
{
    VTPTR p = NULL;
    if(root == NULL)
        cout << "NULL";
    else
    {
        p = root->right;//

        root->right = p->left;
        p->left = root;
    }
    return p;
}

VTPTR Rotate_Right(VTPTR root)
{
    VTPTR p = NULL;
    if(root == NULL)
        cout << "NULL";
    else
    {
        p = root->left;

        root->left = p->right;
        p->right = root;
    }
    return p;
}

VTPTR insertTree(VTPTR &p, int k, VATTU info)
{
    if(p == NULL)
    {
        p = newNode(k, info);
        return p;
    }
    if(k < p->key)
        p->left = insertTree(p->left, k, info);
    else if(k > p->key)
        p->right = insertTree(p->right, k, info);
    else
        return p;//duplicate value

    int bf = getbf(p);
    if(bf > 1 && k < p->left->key)
        return Rotate_Right(p);
    if(bf > 1 && k > p->left->key)
    {
        p->left = Rotate_Left(p->left);
        return Rotate_Right(p);
    }
    if(bf < -1 && k > p->right->key)
        return Rotate_Left(p);
    if(bf < -1 && k < p->right->key)
    {
        p->right = Rotate_Right(p->right);
        return Rotate_Left(p);
    }
    return p;
}

VTPTR removeNode(VTPTR &p, int k)//hàm loại bỏ node trong tree
{
    if(p->key == k)
    {
        rp = p;
        if(p->left == NULL) p = rp->right;
        else if(p->right == NULL) p = rp->left;
        else remove_case_3(p->left);
        delete(rp);
    }
    else if(k < p->key)
        p->left = removeNode(p->left, k);
    else if(k > p->key)
        p->right = removeNode(p->right, k);

    int bf = getbf(p);
    if(bf > 1 && getbf(p->left) == 1)
        return Rotate_Right(p);
    if(bf > 1 && getbf(p->left) == -1)
    {
        p->left = Rotate_Left(p->left);
        return Rotate_Right(p);
    }
    if(bf < -1 && getbf(p->right) == -1)
        return Rotate_Left(p);
    if(bf < -1 && getbf(p->right) == 1)
    {
        p->right = Rotate_Right(p->right);
        return Rotate_Left(p);
    }
    return p;
}

void remove_case_3(VTPTR &r)//hàm loại bỏ node trong tree (trường hợp thứ 3)
{
    if(r->right != NULL)
        remove_case_3(r->right);
    else
    {
        rp->key = r->key;
        rp = r;
        r = rp->left;
    }
}

VATTU searchTree(const VTPTR &root, int k)
{
    VTPTR p = root;
    while(p != NULL && k!=p->key)
        if(k < p->key)
            p = p->left;
        else
            p = p->right;
    return p->info;
}

void infokeyModify(KPTR &head, int k, char* tenvt)
{
    for(KPTR p = head; ;p = p->next)
    {
        if(p->key == k)
        {
            arrCopy(p->tenvt, 0, tenvt);
            return;
        }
    }
}

void infovtModify(VTPTR &p, int k, VATTU inf)//ham thay doi thong tin trong tree dua tren bien inf
{
    if(k == p->key)
        p->info = inf;
    else if(k < p->key)
        infovtModify(p->left, k, inf);
    else if(k > p->key)
        infovtModify(p->right, k, inf);
}

KPTR mergeList(KPTR &headA, KPTR &headB)//sort List
{
    KPTR headC = NULL, tail = NULL;

    if(strComp(headA->tenvt, headB->tenvt) == 1)//headA->tenvt > headB->tenvt
    {
        tail = headC = headB;
        headB = headB->next;
    }
    else
    {
        tail = headC = headA;
        headA = headA->next;
    }
    tail->next = NULL;

    while(true)
    {
        if(headA == NULL)
        {
            tail->next = headB;
            break;
        }
        else if(headB == NULL)
        {
            tail->next = headA;
            break;
        }

        if(strComp(headA->tenvt, headB->tenvt) == 1)//headA->tenvt > headB->tenvt
        {
            tail->next = headB;
            headB = headB->next;
        }
        else//headA->tenvt < headB->tenvt
        {
            tail->next = headA;
            headA = headA->next;
        }
        tail = tail->next;
        tail->next = NULL;
    }
    return headC;
}

KPTR MergeSort(KPTR &head)//MergeSort: sap xep lai phan tu trong mang lien ket don
{
    if(head->next == NULL)
        return head;
    else
    {
        KPTR head2 = head, tail = head;
        while(tail->next != NULL)
        {
            tail = tail->next;
            if(tail->next != NULL)
            {
                tail = tail->next;
                head2 = head2->next;
            }
        }

        tail = head2;
        head2 = head2->next;
        tail->next = NULL;

        head = MergeSort(head);
        head2 = MergeSort(head2);

        return mergeList(head, head2);
    }
}

void vtDisplay(VATTU inf, int col, int row)//ham hien thi thong tin vat tu
{
    gotoxy(col, row+1); cout << inf.tenvt;
    gotoxy(col, row+3); cout << inf.don_vi_tinh;
    gotoxy(col, row+5); cout << inf.soluongton;
}

int soVT(KPTR &head) //ham tra ve so phan tu cua keyArr
{
    int item = 0;
    for(KPTR p = head; p!=NULL; p=p->next)
       item += 1;
    return item;
}

int* convert_keyArr(KPTR &keyArr, bool modify, int &soKey)//chuyen chuoi link list keyArr sang mang 1 chieu
{
    int* key = new int[soVT(keyArr)];
    int i=0;
    for(KPTR p = keyArr; p!=NULL; p=p->next)
        if(modify && p->flag)
        {
            key[i] = p->key;
            i++;
        }
        else if(!modify)
        {
            key[i] = p->key;
            i++;
        }
    soKey = i;
    return key;
}

void dsvtDisplay(VTPTR &root, KPTR &head, int col, int row, bool display_mavt)//hàm hiển thị tất cả thông tin vt có trong tree
{
    DELCOLOR(col, row, 68, soVT(head)+3);//xóa dsvt cũ trước khi hiển thị dsvt mới
    gotoxy(col,row);
    cout << "MA VAT TU   " << char(179);
    gotoxy(col+19, row);
    cout << "TEN VAT TU      "<< char(179);
    gotoxy(col+37, row);
    cout << "SO LUONG TON  "<< char(179);
    gotoxy(col+54,row);
    cout << "DON VI TINH";
    VATTU info;//biến tạm luu thông tin của vt
    gotoxy(col, row+1);
    for(int j=0; j<65; j++)
    {
        if(j == 12 || j == 35 || j == 51)
            cout << char(197);
        else
            cout << char(196);
    }
    int i=0;
    for(KPTR p = head; p!=NULL; p=p->next)
    {
        info = searchTree(root, p->key);//tìm vt trong tree qua khóa và đưa info vào info để xử lí
        if(display_mavt)//dựa vào display_mavt để xem có hiển thị đc hay ko mavt
        {
            gotoxy(col, row+i+2);
            cout << info.mavt <<endl;
        }
        gotoxy(col+12, row+i+2);
        cout << char(179)<< " " <<info.tenvt <<endl;
        gotoxy(col+35, row+i+2);
        cout << char(179) <<"   "<<info.soluongton << endl;
        gotoxy(col+51, row+i+2);
        cout << char(179) <<"    "<<info.don_vi_tinh << endl;
        i++;
    }
    gotoxy(0, 0);//đi lên đầu
}

void deleteVT(VTPTR &root, KPTR &keyArr, int k)//hàm xóa vật tư
{
    delete_Key(keyArr, k);//xoa node tren mang keyArr
    root = removeNode(root, k);//xóa node trên tree dựa vào key_return1
}

bool delmultiVT(VTPTR &p, KPTR &keyArr, int* flag, int MAX)//tổng hợp các vật tư cần xóa ->xóa 1 thể qua các khóa trong chuỗi flag
{
    bool swit = true;
    for(int j=0; j<MAX; j++)
        if(flag[j] != 0){
            swit = false;
            break;
        }
    if(!swit)
    {
        if(exitpop(85, 20, MODE_3))
            for(int i=0; i<MAX; i++)
                if(flag[i] != 0)
                    deleteVT(p, keyArr, flag[i]);
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////////////////

//////////////////////////FOR NHAN VIEN//////////////////////////////
int strComp_v2(NHANVIEN left, NHANVIEN right)
{
    int i=0, j=0;
    while(true)
    {
        if(left.ten[i] != char(32))
        {
            if(right.ten[j] != char(32))
            {
                if(left.ten[i] == right.ten[j])
                {
                    i++;
                    j++;
                }
                else if(left.ten[i] > right.ten[j])
                    return 1;//ten left lớn hơn ten right
                else
                    return -1;//ten left bé hơn ten right
            }
            else j++;
        }
        else i++;
        if(left.ten[i] == NULL && right.ten[j] == NULL) break;//ten left bằng ten right
    }
    i=0; j=0;
    while(true)
    {
        if(left.hoten[i] != char(32))
        {
            if(right.hoten[j] != char(32))
            {
                if(left.hoten[i] == right.hoten[j])
                {
                    i++;
                    j++;
                }
                else if(left.hoten[i] > right.hoten[j])
                    return 1;//hoten left lớn hơn hoten right
                else
                    return -1;//hoten left bé hơn hoten right
            }
            else j++;
        }
        else i++;
        if(left.hoten[i] == NULL && right.hoten[j] == NULL) break;//hoten left bằng hoten right
    }
}

void relocNV(Listnv &dsnv)//selection sort
{
    if(dsnv.n == 1)
        return;
    else
    {
        int i,j;
        NHANVIEN x;
        for(int i=1; i<dsnv.n; i++)
        {
            x = *(dsnv.nvnode[i]);
            for (j=i-1 ;j>=0 ;j--)
            {
                if(strComp_v2(x, *(dsnv.nvnode[j])) == -1)
                    *(dsnv.nvnode[j+1]) = *(dsnv.nvnode[j]);
                else break;
            }
            *(dsnv.nvnode[j+1])= x;
        }
    }
}

void dsnvDisplay(Listnv &ds, int col, int row, bool manvdis)
{
    DELCOLOR(col, row, 80, ds.n+3);
    gotoxy(col,row);
    cout << "MA NHAN VIEN " << char(179);
    gotoxy(col+18, row);
    cout << "TEN    " << char(179);
    gotoxy(col+37, row);
    cout << "HO VA TEN           " << char(179);
    gotoxy(col+60,row);
    cout << "GIOI TINH";
    gotoxy(col, row+1);
    for(int j=0; j<70; j++)
    {
        if(j == 13 || j == 25 || j==57)
            cout << char(197);
        else
            cout << char(196);
    }
    for(int i=0; i < ds.n; i++)
    {
        DELCOLOR(col, row+i+2, 70, 1);
        if(manvdis){
            gotoxy(col+5 ,row+i+2);
            cout << ds.nvnode[i]->manv;
        }
        gotoxy(col+13, row+i+2);
        cout << char(179)<<" "<<ds.nvnode[i]->ten;
        gotoxy(col+25, row+i+2);
        cout << char(179)<<" "<<ds.nvnode[i]->hoten;
        gotoxy(col+57,row+i+2);
        if(ds.nvnode[i]->gioitinh == '2')cout << char(179)<<"    Nam";
        else cout << char(179)<<"   Nu";
    }
}

int setVal(int *manv, Listnv &ds)
{
    int num = 0;
    for(int i=0; i<ds.n; i++)
    {
        manv[i] = ds.nvnode[i]->manv;
        num++;
    }
    return num;
}

int nvDisplay(NHANVIEN info)
{
    gotoxy(10+11, 5+1);
    cout << info.hoten;
    gotoxy(10+11, 5+3);
    cout << info.ten;
    SetColor(WHITE);
    SetBGColor(RED);
    if(info.gioitinh == '2')
    {
        gotoxy(10+13, 5+5);
        cout << "NAM";
    }
    else
    {
        gotoxy(10+13+12, 5+5);
        cout << "NU";
    }
    Normal();
}

int searchManv(Listnv &ds, int code)
{
    for(int i=0; i<ds.n; i++)
    {
        if(code == ds.nvnode[i]->manv)
            return i;
    }
    return -1;
}

void deleteNV(Listnv &ds, int index)
{
    if(index == ds.n-1)
    {
        delete(ds.nvnode[index]);
        ds.n--;
        return;
    }
    int i=index;
    while(i<ds.n-1)
    {
        *(ds.nvnode[i]) = *(ds.nvnode[i+1]);
        i++;
    }
    delete(ds.nvnode[ds.n-1]);
    ds.n--;
}

bool delmultiNV(Listnv& ds, int *flag, int MAX)
{
    bool swit = true;
    for(int j=0; j<MAX; j++)
        if(flag[j] != 0)
        {
            swit = false;
            break;
        }
    if(!swit)
    {
        if(exitpop(85, 20, MODE_3))
            for(int i=0; i<MAX; i++)
                if(flag[i] != 0)
                    deleteNV(ds, searchManv(ds, flag[i]));
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////FOR HOA DON/////////////////////////////////
date dateInfo()
{
    date info;
    time_t now = time(NULL);
    tm* getime = localtime(&now);
    info.thang = getime->tm_mon+1;
    info.ngay = getime->tm_mday;
    info.nam = getime->tm_year+1900;
    info.gio = getime->tm_hour;
    info.phut = getime->tm_min;
    return info;
}

int getSLT(const VTPTR &root, int k)
{
    VTPTR p = root;
    while(p != NULL && k!=p->key)
        if(k < p->key)
            p = p->left;
        else
            p = p->right;
    return p->info.soluongton;
}

void putSLT(VTPTR &root, int k, int SLT)
{
    if(root->key == k)
        root->info.soluongton = SLT;
    else if(k < root->key)
        putSLT(root->left, k, SLT);
    else if(k > root->key)
        putSLT(root->right, k, SLT);
}

void updateVT(VTPTR &dsvt, DS_CTHD cthd, char loaiHD)
{
    int key, changeSLT, newSLT, oldSLT;
    for(int i=0; i<cthd.n; i++)
    {
        changeSLT = cthd.cthd[i]->soluong;//
        key = numConvert_reverse(cthd.cthd[i]->mactvt);
        oldSLT = getSLT(dsvt, key);
        if(loaiHD == 'N')
            newSLT = oldSLT + changeSLT;
        else if(loaiHD == 'X')
            newSLT = oldSLT - changeSLT;
        putSLT(dsvt, key, newSLT);
    }
}

int dshdDisplay(Listnv &dsnv, int nvindex, int col, int row)
{
    gotoxy(col, row);
    cout << "STT   |";
    gotoxy(col+7, row);
    cout << "     SO HOA DON      |";
    gotoxy(col+29, row);
    cout << "     THOI GIAN     |";
    gotoxy(col+49, row);
    cout << "  LOAI";
    gotoxy(col-3, row+1);
    for(int j=0; j<60; j++)
    {
        if(j == 6+3 || j == 28+3 || j == 48+3)
            cout << char(197);
        else
            cout << char(196);
    }
    int i=0;
    for(PTRHD p = dsnv.nvnode[nvindex]->first; p != NULL; p = p->next)
    {
        gotoxy(col, row+2+i);
        cout << i+1;
        gotoxy(col+6, row+2+i);
        cout <<"| " <<p->info.soHD;
        gotoxy(col+28, row+2+i);
        cout <<"| "<< p->info.thoigian.ngay <<"/"<<p->info.thoigian.thang <<"/"<<p->info.thoigian.nam << "--" << p->info.thoigian.gio << ":" << p->info.thoigian.phut;
        gotoxy(col+48, row+2+i);
        cout <<"|   "<<p->info.loai;
        i++;
    }
    return i;//tra ve so luong hd
}

void mahdGen_sub(int MAX, int val, char *a, int a_index)
{
    char *temp = new char[MAX]{'0'};
    numConvert(val, temp, MAX);
    arrCopy(a, a_index, temp);
    delete(temp);
}

void mahdGen(char *maHD, int manv, date obj, char loaiHD, int soCTHD)
{
    mahdGen_sub(4, manv, maHD, 0);
    mahdGen_sub(3, obj.ngay, maHD, 3);
    mahdGen_sub(3, obj.thang, maHD, 5);
    mahdGen_sub(3, obj.gio, maHD, 7);
    mahdGen_sub(3, obj.phut, maHD, 9);
    maHD[11] = loaiHD;
    mahdGen_sub(8, soCTHD, maHD, 12);
    maHD[19] = NULL;
}

void addHD(dshd val, Listnv &dsnv, int nvindex)
{
    //create a new node
    PTRHD newNode = new node_hd;
    newNode->info = val;
    newNode->next = NULL;

    //if head is NULL, it is an empty list
    if(dsnv.nvnode[nvindex]->first == NULL){
        dsnv.nvnode[nvindex]->first = newNode;
    }
    //Otherwise, find the last node and add the newNode
    else
    {
        PTRHD lastNode = dsnv.nvnode[nvindex]->first;

        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        //add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
}

void dshdDefault(dshd &obj)
{
    chitietHD *p;
    obj.ptr = new DS_CTHD;
    obj.loai = NULL;
}

void dshd_Save_Procedure(dshd &temphd, Listnv &dsnv, VTPTR &dsvt, int nvindex, int &slhd)
{
    dsnv.nvnode[nvindex]->state = '1';//trang thái thay đổi khi thông tin trong field nv có sự thay đổi
    temphd.thoigian = dateInfo();//set thời gian cho biến temphd
    mahdGen(temphd.soHD, dsnv.nvnode[nvindex]->manv, temphd.thoigian, temphd.loai, temphd.ptr->n);//tạo mã hóa đơn dựa vào mã nv, thời gian, loại hd, số cthd
    addHD(temphd, dsnv, nvindex);//đẩy thông tin hóa đơn vào thông tin nhân viên
    updateVT(dsvt, *temphd.ptr, temphd.loai);
    slhd = dshdDisplay(dsnv, nvindex, 10-6, 5+13);//hiển thị các thông tin hóa đơn của nhân viên
    dshdDefault(temphd);
    DELCOLOR(10+14-8, 5+3, 1, 1);
    DELCOLOR(65+1, 5+13, 84, 28);
}

void hdInfo(Listnv &dsnv, VTPTR &dsvt, KPTR &keyArr)//1nd main fucntion
{
    preFram(MODE_5);
    dshd temphd;//biến temp lưu thông tin người dùng nhập vào
    temphd.ptr = new DS_CTHD;//khởi tạo danh sách chi tiết hóa đơn
    int key = -1, nvindex, slhd=0;
    bool loop = ON;
    int opt;
    int choose = 0;
    do
    {
        DELCOLOR(65+30+51, 5, 11, 11);
        instruct(65+30+40, 6, "INFO");
        opt = MENU_DONG_DOC(hd_menu, item_hd, 10+1-8, 5+1, OFF, ON, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1://NHAP MA NHAN VIEN
            if(temphd.ptr->n != 0)//điều kiện đúng khi có cthd đc nhập vào -> tránh việc vô tình nhân viên thay đổi mã
            {
                if(exitpop(65+30+10, 5, MODE_2))//hỏi xem người dùng có muốn lưu ds cthd ko
                    dshd_Save_Procedure(temphd, dsnv, dsvt, nvindex, slhd);
                else
                {
                    choose = --opt;
                    break;
                }
            }
            DELCOLOR(10-9, 5+13, 60, 2+slhd);
            DELCOLOR(10+14-8, 5+1, 3, 1);
            FRAME(BLUE, 10+18-8, 5+1, 30, 1);
            while(true)
            {
                key = nhapSo(3 ,10+14-8, 5+1);
                nvindex = searchManv(dsnv, key);
                if(nvindex != -1)
                {
                    gotoxy(10+18-8, 5+1);
                    highlight3();
                    cout << dsnv.nvnode[nvindex]->hoten;
                    Normal();
                    if(dsnv.nvnode[nvindex]->first != NULL)
                        slhd = dshdDisplay(dsnv, nvindex, 10-6, 5+13);//hiển thị các thông tin hóa đơn của nhân viên
                    break;
                }
                else
                {
                    POP_UP(10+1-8, 5+10, 10+14-8, 5+1, 3, MODE_10);
                    key = -1;
                    break;
                }
            }
            choose = --opt;
        break;
        case 2://NHAP LOAI HD
            DELCOLOR(10+14-8, 5+3, 1, 1);
            while(true)
            {
                char loaiHD[2];
                nhapChu(loaiHD, 2, 10+14-8, 5+3, OFF);
                if(loaiHD[0] == 'x' || loaiHD[0] == 'n')
                {
                    temphd.loai = loaiHD[0] - 32;
                    break;
                }
                else
                {
                    POP_UP(10+1-8, 5+10, 10+14-8, 5+3, 1, MODE_13);
                    temphd.loai = NULL;
                    break;
                }
            }
            choose = --opt;
        break;
        case 3://CHI TIET HOA DON
            if(key != -1 &&  temphd.loai != NULL)
                cthdInfo(dsvt, keyArr, temphd.loai, temphd.ptr);
            else
                POP_UP(10+1-8, 5+10, 10+1-8, 5+10, 0, MODE_5);
            choose = --opt;
        break;
        case 4://IN HOA DON
            if(slhd != 0)
            {
                instruct(65+30+40, 6, "DELETE");
                while(true)
                {
                    DELCOLOR(1, 5+15, 2, slhd);
                    int *HD = new int[slhd];//tạo chuỗi lưu mã nv
                    for(int i=0; i<slhd ;i++) HD[i] = i+1;
                    int *flag = MENU_DONG_DOC_FOR_NUMBER_v2(HD, slhd, 10-6, 5+15, WHITE, RED);
                    if(inDSHD(dsnv, nvindex, flag, slhd))
                    {
                        delete(HD);
                        delete(flag);
                        break;
                    }
                }
            }
            choose = --opt;
        break;
        case 0://SAVE OR EXIT
            {
                int opt2 = MENU_DONG_DOC(save_menu, 2, 10+48+1-8, 5, ON, OFF, 2, WHITE, RED);
                switch(opt2)
                {
                case 1://SAVE
                    if(key != -1 && temphd.loai != NULL && temphd.ptr->n != 0)
                    {
                        if(exitpop(65+30+10, 5, MODE_2))
                            dshd_Save_Procedure(temphd, dsnv, dsvt, nvindex, slhd);
                    }
                    else
                        POP_UP(10+1-8, 5+10, 10+1-8, 5+10, 0, MODE_5);
                    break;
                case 2://EXIT
                    if(temphd.ptr->n != 0)
                    {
                        if(exitpop(65+30+10, 5, MODE_2))//hỏi xem người dùng có muốn lưu ds cthd ko
                            dshd_Save_Procedure(temphd, dsnv, dsvt, nvindex, slhd);
                    }
                    delete(temphd.ptr);
                    loop = OFF;
                    break;
                case -1://LEFT
                    break;
                }
            }
        break;
        }
    }
    while(loop);
}

bool inDSHD(Listnv &dsnv, int nvindex, int *flag, int MAX)
{
    bool swit = true;
    NHANVIEN nv = *dsnv.nvnode[nvindex];
    for(int i=0; i<MAX; i++)
        if(flag[i] != 0)
        {
            swit = false;
            break;
        }
    if(!swit)
    {
        if(exitpop(65+30+10, 5, MODE_3))
        {
            int i = 0;
            for(PTRHD p = nv.first; p!=NULL; p=p->next, i++)
                if(flag[i] != 0)
                    inHD(nv, p->info);
            POP_UP(10+1-8, 5+10, 10+14-8, 5+1, 0, MODE_16);
        }
        return false;
    }
    return true;
}

void inHD(NHANVIEN nv, dshd info)
{
    char slash[] = "/";
    char extend[] = ".txt";
    char folder[100] = "thong tin vat tu/";
    mkdir(folder);
    appArr(folder, nv.hoten, folder);
    mkdir(folder);
    appArr(folder, slash, folder);
    appArr(folder, info.soHD, folder);
    appArr(folder, extend, folder);
    //tìm thông tin hóa đơn dựa vào sô
    FILE *handle = fopen(folder, "w");
    if(handle == NULL)
    {
        cout << "ko mo dc";
        return;
    }
    fputs("\t\t\tHOA DON VAT TU\n", handle);
    fprintf(handle, "\tNGUOI TAO: %s\n\n", nv.hoten);
    fprintf(handle, "\tTHOI GIAN TAO: %d:%d %d/%d/%d\n\n",
            info.thoigian.gio,
            info.thoigian.phut,
            info.thoigian.ngay,
            info.thoigian.thang,
            info.thoigian.nam);
    if(info.loai == 'X') fputs("\tLOAI HOA DON: XUAT\n\n", handle);
    else fputs("\tLOAI HOA DON: NHAP\n\n", handle);
    fputs("   TEN VAT TU           | SL         | DON GIA    |  TRI GIA\n", handle);
    fputs("   ---------------------------------------------------------\n", handle);
    chitietHD temp;
    char* val = NULL;
    char buffer[74];
    buffer[72] = char(10);//new line
    buffer[73] = NULL;
    for(int j=0; j<info.ptr->n; j++)
    {
        temp = *info.ptr->cthd[j];
        for(int i=0; i<74; i++)
        {
            if(i==0 || i==1 || i==2 || i==23 || i==25 || i==36 || i==38 || i==49 || i==51)
                buffer[i] = ' ';//space
            else if(i==24 || i==37 || i==50)
                buffer[i] = '|';//character '|'
            else if(i==3)
            {
                i = i + arrCopy(buffer, i, temp.tenctvt);
                while(i < 23) {buffer[i] = char(32); i++;}
                i--;
            }
            else if(i==26)
            {
                val = numConvert_v2(temp.soluong);
                i = i + arrCopy(buffer, i, val);
                while(i < 36) {buffer[i] = char(32); i++;}
                i--;
                delete(val);
            }
            else if(i==39)
            {
                val = numConvert_v2(temp.dongia);
                i = i + arrCopy(buffer, i, val);
                while(i < 49) {buffer[i] = char(32); i++;}
                i--;
                delete(val);
            }
            else if(i==52)
            {
                val = numConvert_v2(totalCTHD(temp));
                i = i + arrCopy(buffer, i, val);
                while(i < 72) {buffer[i] = char(32); i++;}
                delete(val);
            }
        }
        fputs(buffer, handle);
    }
    fputs("   ---------------------------------------------------------\n", handle);
    fprintf(handle, "                                      TONG TRI GIA:%d\n", info.ptr->total);
    fclose(handle);
}

char* numConvert_v2(int num)
{
    int MAX=0, temp = num;
    while(temp >= 1)
    {
        temp /= 10;
        MAX++;
    }
    char *val = new char[MAX+1]{NULL};
    numConvert(num, val, MAX+1);
    return val;
}

void appArr(char *arr1, char *arr2, char *arr3)
{
    int MAX=0;
    char temp[100], swit = '0';
    int i=0;
    for(;;i++)
    {
        if(arr1[i] != NULL  && swit == '0')
        {
            temp[MAX] = arr1[i];
            MAX++;
            continue;
        }
        else if(arr1[i] == NULL  && swit == '0')
        {
            i = -1;
            swit = '1';
        }
        else if(arr2[i] != NULL && swit == '1')
        {
            temp[MAX] = arr2[i];
            MAX++;
            continue;
        }
        else if(arr2[i] == NULL && swit == '1')
        {
            i = 0;
            temp[MAX] = NULL;
            MAX++;//NULL
            swit = '0';
            break;
        }
    }
    for(; i!=MAX; i++)
        arr3[i] = temp[i];
}

bool checkVT(KPTR &head, int key)
{
    for(KPTR p = head; p!=NULL; p=p->next)
        if(key == p->key)
            return true;
    return false;
}

void cthdDefault(chitietHD &obj)
{
    obj.mactvt[0] = NULL;
    obj.dongia = -1;
    obj.soluong = -1;
    obj.vat = -1;
}

void cthdDisplay(DS_CTHD obj, int col, int row, bool mavt_display)
{
    if(obj.n == 0) return;
    gotoxy(col, row);
    cout << "MA VAT TU  |";
    gotoxy(col+14, row);
    cout << "     TEN VAT TU      |";
    gotoxy(col+36, row);
    cout << " SO LUONG |";
    gotoxy(col+48, row);
    cout << "  DON GIA   |";
    gotoxy(col+61, row);
    cout << " (%)VAT |";
    gotoxy(col+70, row);
    cout << "  TRI GIA";
    gotoxy(col, row+1);
    for(int j=0; j<84; j++)
    {
        if(j == 11 || j == 35 || j == 46 || j == 60 || j == 69)
            cout << char(197);
        else
            cout << char(196);
    }
    int cost;
    float total = 0;
    chitietHD temp;
    int i=0;
    for(; i<obj.n; i++)
    {
        temp = *(obj.cthd[i]);
        if(mavt_display)
        {
            gotoxy(col, row+2+i);
            cout << temp.mactvt;
        }
        gotoxy(col+11, row+2+i);
        cout <<"|  "<<temp.tenctvt;
        gotoxy(col+35, row+2+i);
        cout <<"| "<<temp.soluong;
        gotoxy(col+46, row+2+i);
        cout <<"| "<<temp.dongia;
        gotoxy(col+60, row+2+i);
        cout <<"|  "<<temp.vat;
        cost = temp.soluong*temp.dongia;
        gotoxy(col+69, row+2+i);
        cout <<"| "<<cost+cost*(float(temp.vat)/100);
        total += cost+cost*(float(temp.vat)/100);
    }
    gotoxy(col+63, row+2+i+1);
    cout << "TOTAL = " << total;
}

void demo(KPTR &keyArr, DS_CTHD* dscthd, VTPTR &root)
{
    chitietHD temp;
    int key, num;
    int* mavt = convert_keyArr(keyArr, OFF, num);
    VATTU tempvt;
    for(int i=0; i<20; i++)
    {
        dscthd->cthd[i] = new chitietHD;
        temp.dongia = rand()%1000;
        temp.soluong= rand()%50;
        key = mavt[rand()%(num-1)];
        tempvt = searchTree(root, key);
        arrCopy_v2(temp.tenctvt, tempvt.tenvt, 20);
        numConvert(key, temp.mactvt, 10);
        temp.vat = rand()%50;
        dscthd->total += totalCTHD(temp);
        *(dscthd->cthd[i]) = temp;
    }
    dscthd->n = 20;
}

void deleteCTHD(DS_CTHD* &dscthd, int val)
{
    int i=0;
    for(; i<dscthd->n; i++)
        if(numConvert_reverse(dscthd->cthd[i]->mactvt) == val)
            break;
    delete(dscthd->cthd[i]);//xóa phần tử cthd ở chỉ số index
    for(; i<dscthd->n-1; i++)//sắp lại mảng cthd
        dscthd->cthd[i] = dscthd->cthd[i+1];
    dscthd->cthd[dscthd->n-1] = NULL;
    dscthd->n--;
}

bool delmultiCTHD(DS_CTHD* &dscthd, int *flag)
{
    bool swit = true;
    for(int j=0; j<dscthd->n; j++)
        if(flag[j] != 0)
        {
            swit = false;
            break;
        }
    if(!swit)
    {
        if(exitpop(65+30+10, 5, MODE_3))
        {
            for(int i=dscthd->n-1; i >= 0; i--)
            {
                if(flag[i] != 0)
                    deleteCTHD(dscthd, flag[i]);
            }
        }

        return false;
    }
    return true;
}

int setDSCTHD(DS_CTHD* &dscthd, int *arr)
{
    int i=0;
    for(; i<dscthd->n; i++)
        arr[i] = numConvert_reverse(dscthd->cthd[i]->mactvt);
    return i;
}

int totalCTHD(chitietHD val)//h
{
    int sum = val.soluong*val.dongia;
    return sum + sum*(val.vat/100);
}

void cthdInfo(VTPTR dsvt, KPTR &keyArr, char loaiHD, DS_CTHD* dscthd)//2nd main function
{
    chitietHD tempcthd;//khai báo biến tạm để lưu thông tin thông tin nhập
    cthdDefault(tempcthd);//set giá trị default cho tempcthd
    VATTU tempvt;
    if(dscthd->n > 0) cthdDisplay(*(dscthd), 65+1, 5+13, ON);
    bool loop = ON, swit = ON;//công tắc
    int opt, choose = 0;
    do
    {
        DELCOLOR(65+30+51, 5, 11, 11);
        instruct(65+30+40, 6, "INFO");
        if(dscthd->n == MAXVT) swit = OFF;//nếu cthd đạt đến MAXVT thì công tắc OFF
        else swit = ON;//nếu số lượng đang có ít hơn số lượng max thì cho phép thêm
        opt = MENU_DONG_DOC(cthd_menu, item_cthd, 65+1, 5+1, OFF, ON, 2, WHITE, RED, choose);
        switch(opt)
        {
        case 1://NHAP MA VT
            while(swit)
            {
                DELCOLOR(65+13, 5+1, 9, 1);
                int key = nhapSo(9, 65+13, 5+1);
                if(checkVT(keyArr, key))
                {
                    tempvt = searchTree(dsvt, key);
                    tempcthd.tenctvt[arrCopy(tempcthd.tenctvt, 0, tempvt.tenvt)] = NULL;
                    numConvert(key, tempcthd.mactvt, 10);
                    break;
                }
                else
                    POP_UP(65+1, 5+11, 65+13, 5+1, 9, MODE_11);
            }
            if(!swit)
                POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_7);
            choose = --opt;
            break;
        case 2://NHAP SO LUONG
            while(swit)
            {
                DELCOLOR(65+13, 5+3, 10, 1);
                int sl = nhapSo(10, 65+13, 5+3);
                if(loaiHD == 'X' && tempvt.soluongton < sl)
                {
                    gotoxy(65+1+22, 5+11);
                    highlight2();
                    cout << tempvt.tenvt <<" : " << tempvt.soluongton;
                    POP_UP(65+1, 5+11, 65+13, 5+3, 10, MODE_12);
                }
                else
                {
                    tempcthd.soluong = sl;
                    break;
                }
            }
            if(!swit)
                POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_7);
            choose = --opt;
            break;
        case 3://NHAP DON GIA
            while(swit)
            {
                DELCOLOR(65+13, 5+5, 10, 1);
                int dgia = nhapSo(10, 65+13, 5+5);
                if(dgia > 0)
                {
                    tempcthd.dongia = dgia;
                    break;
                }
                else
                    POP_UP(65+1, 5+9, 65+13, 5+5, 10, MODE_13);
            }
            if(!swit)
                POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_7);
            choose = --opt;
            break;
        case 4://NHAP %VAT
            while(swit)
            {
                DELCOLOR(65+13, 5+7, 10, 1);
                int vat_ = nhapSo(10, 65+13, 5+7);
                if(vat_ > 0)
                {
                    tempcthd.vat = vat_;
                    break;
                }
                else if(vat_ == -1)
                    break;
                else
                    POP_UP(65+1, 5+11, 65+13, 5+7, 5, MODE_13);
            }
            if(!swit)
                POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_7);
            choose = --opt;
            break;
        case 5:
            if(swit)
            {
                demo(keyArr, dscthd, dsvt);
                cthdDisplay(*(dscthd), 65+1, 5+13, ON);
            }
            choose = --opt;
            break;
        case 0://SAVE
            {
                int opt2 = MENU_DONG_DOC(save_menu, item_save, 65+30+1, 5, ON, OFF, 2, WHITE, RED);
                switch(opt2)
                {
                case 1://save
                    if(tempcthd.mactvt[0] != NULL || tempcthd.dongia != -1 || tempcthd.soluong != -1 || tempcthd.vat != -1)
                    {
                        if(exitpop(65+30+10, 5))
                        {
                            dscthd->cthd[dscthd->n] = new chitietHD;//khởi tạo phần tử cthd
                            *(dscthd->cthd[dscthd->n]) = tempcthd;//đẩy thông tin vừa nhập vào phần tử mới tạo
                            dscthd->total += totalCTHD(tempcthd);
                            dscthd->n++;//tăng số cthd trong mảng danh sách chi tiết hóa đơn
                            cthdDisplay(*dscthd, 65+1, 5+13, ON);//hiển thị danh sách cthd
                            cthdDefault(tempcthd);//set lại giá trị mặc định cho biến tạm tempcthd
                            DELCOLOR(65+13, 5+1, 9, 1);
                            DELCOLOR(65+13, 5+3, 10, 1);
                            DELCOLOR(65+13, 5+5, 10, 1);
                            DELCOLOR(65+13, 5+7, 5, 1);
                        }
                    }
                    else
                        POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_5);
                    break;
                case 2://exit
                    loop = OFF;
                    break;
                case 3://delete
                    if(dscthd->n != 0)
                    {
                        instruct(65+30+40, 6, "DELETE");
                        while(true)
                        {
                            DELCOLOR(65+1, 5+13, 84, 28);
                            cthdDisplay(*dscthd, 65+1, 5+13, OFF);
                            int VT[dscthd->n];//tạo chuỗi lưu mã nv
                            if(setDSCTHD(dscthd, VT) == 0) break;//set giá trị cho chuỗi maNV qua truy cập chuỗi dsnv
                            int *flag = MENU_DONG_DOC_FOR_NUMBER_v2(VT, dscthd->n, 65+1+4, 5+15, WHITE, RED);
                            if(delmultiCTHD(dscthd, flag))
                            {
                                delete(flag);
                                break;
                            }
                        }
                    }
                    else
                        POP_UP(65+1, 5+11, 65+1, 5+10, 0, MODE_3);
                    break;
                case -1://right
                    break;
                }
            }
            break;
        }
    }
    while(loop);
}

//////////////////////////////////////////////////////////////////////////

/////////////////////////////FOR THONG KE/////////////////////////////////
int timeInterval(date &timeA, date &timeB, int col, int row)
{
    const int item_interval = 2;
    char interval_menu[item_interval][DEFAULT_COL] = {"Tu ngay:", "Den ngay:"};
    const int item_space = 3;
    char space_menu[item_space][DEFAULT_COL] = {" ", " ", " "};

    gotoxy(col, row);
    cout << "Tu ngay:    /   /     ,Den ngay:    /   /     ";
    date Present = dateInfo();
    bool loop = ON, loop1 = ON, loop2 = ON;
    int opt, opt1, opt2;
    int choose = 0, choose1 = 0, choose2 = 0;
    do
    {
        opt = MENU_DONG_NGANG(interval_menu, item_interval, col, row, 23, ON, OFF, WHITE, RED, choose);
        switch(opt)
        {
        case 1:
            do
            {
                opt1 = MENU_DONG_NGANG(space_menu, item_space, col+9, row, 4, ON, OFF, WHITE, RED, choose1);
                switch(opt1)
                {
                case 1:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+10, row, 2, 1);
                        timeA.ngay = nhapSo(2, col+10, row);
                        if(timeA.ngay <= 31)
                        {
                            DELCOLOR(col+50, row, 13, 1);
                            break;
                        }
                    }
                    choose1 = opt1;
                break;
                case 2:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+14, row, 2, 1);
                        timeA.thang = nhapSo(2, col+14, row);
                        if(timeA.thang <= 12)
                        {
                            DELCOLOR(col+50, row, 13, 1);
                            break;
                        }
                    }
                    choose1 = opt1;
                break;
                case 3:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+18, row, 4, 1);
                        timeA.nam = nhapSo(4, col+18, row);
                        if(timeA.nam <= Present.nam && timeA.nam != 0)
                        {
                            loop1 = OFF;
                            DELCOLOR(col+50, row, 13, 1);
                            gotoxy(col+17, row); cout << " ";
                            choose = opt;
                            break;
                        }
                    }
                break;
                case ESCAPE:
                    loop1 = OFF;
                break;
                }
            }
            while(loop1);
        break;
        case 2:
            do
            {
                opt2 = MENU_DONG_NGANG(space_menu, item_space, col+33, row, 4, ON, OFF, WHITE, RED, choose2);
                switch(opt2)
                {
                case 1:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+34, row, 2, 1);
                        timeB.ngay = nhapSo(2, col+34, row);
                        if(timeB.ngay <= 31)
                        {
                            DELCOLOR(col+50, row, 13, 1);
                            break;
                        }
                    }
                    choose2 = opt2;
                break;
                case 2:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+38, row, 2, 1);
                        timeB.thang = nhapSo(2, col+38, row);
                        if(timeB.thang <= 12)
                        {
                            DELCOLOR(col+50, row, 13, 1);
                            break;
                        }
                    }
                    choose2 = opt2;
                break;
                case 3:
                    while(true)
                    {
                        gotoxy(col+50, row); highlight3(); cout << "VUI LONG NHAP"; Normal();
                        DELCOLOR(col+42, row, 4, 1);
                        timeB.nam = nhapSo(4, col+42, row);
                        if(timeA >= timeB)
                        {
                            loop2 = OFF;
                            choose = 0;
                            gotoxy(col+41, row); cout << " ";
                            gotoxy(col, row); cout << "Tu ngay:";
                            gotoxy(col+23, row); cout << "Den ngay:";
                            POP_UP(col+50, row, col+50, row+1, 0, MODE_13);
                            break;
                        }
                        else if(timeB <= Present)
                        {
                            DELCOLOR(col+50, row, 13, 1);
                            return 0;
                        }
                    }
                break;
                case ESCAPE:
                    loop2 = OFF;
                break;
                }
            }
            while(loop2);
        break;
        case ESCAPE:
            return -1;
        break;
        }
    }
    while(loop);
}

void insertAfter(PTRHD &head, dshd val)//g
{
    PTRHD newNode = new node_hd;
    newNode->info = val;
    newNode->next = NULL;
    if(head == NULL)
    {
        head = newNode;
        return;
    }
    PTRHD p = head, q = p;
    if(p->info.thoigian >= val.thoigian)//insertFirst
    {
        newNode->next = head;
        head = newNode;
        return;
    }
    else p = p->next;
    for(;;p=p->next)
    {
        if(p == NULL)//insertLast
        {
            q->next = newNode;
            return;
        }
        if(p->info.thoigian >= val.thoigian)//insert after
        {
            newNode->next = q->next;
            q->next = newNode;
            return;
        }
        q=p;
    }
}

int thongkeHD(Listnv &dsnv, date timeA, date timeB, int col, int row)//g
{
    PTRHD p = NULL;//biến quản lí danh sách hd nhân viên
    PTRHD head = NULL;//danh sách hd thống kê
    for(int i=0; i<dsnv.n; i++)//duyệt qua từng nhân viên trong ds
        for(p = dsnv.nvnode[i]->first; p!=NULL; p=p->next)//duyệt qua danh sách hóa đơn của nhân viên
            if(timeA < p->info.thoigian && p->info.thoigian < timeB)//check xem thời gian của node hd hiện tại có lớn hơn timeB ko
                //nếu ko thì thỏa điều kiện lớn hơn timeA, nhỏ hơn timeB
                //thêm node mới vào cuối danh sách head
                insertAfter(head, p->info);

    //display
    gotoxy(col, row);
    cout << "     SO HOA DON      |";
    gotoxy(col+22, row);
    cout << "     THOI GIAN     |";
    gotoxy(col+42, row);
    cout << " LOAI |";
    gotoxy(col+49, row);
    cout << "       HO VA TEN         |";
    gotoxy(col+76, row);
    cout << "  TRI GIA HD";
    gotoxy(col, row+1);
    for(int j=0; j<90; j++)
    {
        if(j == 21 || j == 41 || j == 48 || j == 74)
            cout << char(197);
        else
            cout << char(196);
    }
    int i=0, j;
    char temp[4]; temp[3] = NULL;
    p = head;
    for(; p != NULL; p = p->next)
    {
        temp[0] = p->info.soHD[0];
        temp[1] = p->info.soHD[1];
        temp[2] = p->info.soHD[2];
        gotoxy(col, row+2+i);
        cout << p->info.soHD;
        gotoxy(col+21, row+2+i);
        cout <<"| "<<p->info.thoigian.ngay <<"/"<<p->info.thoigian.thang <<"/"<<p->info.thoigian.nam << "--" << p->info.thoigian.gio << ":" << p->info.thoigian.phut;
        gotoxy(col+41, row+2+i);
        cout <<"|  "<<p->info.loai;
        gotoxy(col+48, row+2+i);
        j = searchManv(dsnv, numConvert_reverse(temp));
        cout <<"| "<<dsnv.nvnode[j]->hoten;
        gotoxy(col+74, row+2+i);
        cout <<"| "<< p->info.ptr->total;
        i++;
    }
    return i;
}

void insertLast_listvt(listvt* &head, DTVT val)//insert last//h
{
    listvt* newNode = new listvt;
    newNode->info = val;
    newNode->next = NULL;
    if(head == NULL)
        head = newNode;
    else
        for(listvt* p = head;;p=p->next)
        {

            if(p->info.madtvt == val.madtvt)
            {
                p->info.doanhthu += val.doanhthu;
                break;
            }
            if(p->next == NULL)
            {
                p->next = newNode;
                break;
            }
        }
}

void extractListvt(listvt* &head1, listvt* &head2, int val)//h
{
    listvt* last = head2;
    if(last != NULL)
        while(last->next != NULL)
            last = last->next;

    listvt* p = head1, *q;
    if(head1->info.doanhthu == val && last == NULL)
    {
        if(last == NULL) head2 = p;
        else last->next = p;
        head1 = p->next;
        p->next = NULL;
        return;
    }

    for(; p != NULL; p=p->next)
    {
        if(val == p->info.doanhthu)
        {
            if(last == NULL) head2 = p;
            else last->next = p;
            q->next = p->next;
            p->next = NULL;
            return;
        }
        q = p;
    }
}

void find_add_MaxDT(listvt* &thongke_dtvt, listvt* &top10)//h
{
    int i=1;
    listvt* p = thongke_dtvt;
    int MAX = p->info.doanhthu;

    while(i <= 10)
    {
        for(; p != NULL; p = p->next)
            if(MAX < p->info.doanhthu)
                MAX =  p->info.doanhthu;

        p = thongke_dtvt;
        for(; p != NULL; p = p->next)
            if(MAX == p->info.doanhthu)
            {
                extractListvt(thongke_dtvt, top10, MAX);
                p = thongke_dtvt;
                MAX =  p->info.doanhthu;
                break;
            }
        i++;
    }
}

int thongkeVT(Listnv &dsnv, date timeA, date timeB, int col, int row)//h
{
    PTRHD p = NULL;//biến quản lí danh sách hd nhân viên
    listvt* thongkedtvt = NULL;
    listvt* top10 = NULL;
    DTVT temp;
    chitietHD tempcthd;
    for(int i=0; i<dsnv.n; i++)//duyệt qua từng nhân viên trong ds
        for(p = dsnv.nvnode[i]->first; p!=NULL; p=p->next)//duyệt qua danh sách hóa đơn của nhân viên
            if(timeA < p->info.thoigian && p->info.thoigian < timeB && p->info.loai == 'X')//check xem thời gian của node hd hiện tại có lớn hơn timeB ko
                //nếu ko thì thỏa điều kiện lớn hơn timeA, nhỏ hơn timeB
                //thêm node mới vào cuối danh sách head
                    for(int j=0; j<p->info.ptr->n; j++)
                    {
                        tempcthd = *(p->info.ptr->cthd[j]);
                        temp.doanhthu = totalCTHD(tempcthd);
                        temp.tendtvt[arrCopy(temp.tendtvt, 0, tempcthd.tenctvt)] = NULL;
                        temp.madtvt = numConvert_reverse(tempcthd.mactvt);
                        insertLast_listvt(thongkedtvt, temp);
                    }

    find_add_MaxDT(thongkedtvt, top10);
    //display
    gotoxy(col, row);
    cout << "      TEN VAT TU      |";
    gotoxy(col+24, row);
    cout << " DOANH THU";
    gotoxy(col, row+1);
    for(int j=0; j<40; j++)
    {
        if(j == 22)
            cout << char(197);
        else
            cout << char(196);
    }
    int i=0;
    for(listvt* k = top10; k != NULL; k = k->next)
    {
        gotoxy(col, row+2+i);
        cout <<  k->info.tendtvt;
        gotoxy(col+22, row+2+i);
        cout <<"| "<< k->info.doanhthu;
        i++;
    }
    return i;
}

int thongkeDT(Listnv &dsnv, int year, int col, int row)//i
{
    int *thang = new int[13]{0};
    for(int i=0; i<dsnv.n; i++)//duyệt qua từng nhân viên trong ds
        for(PTRHD p = dsnv.nvnode[i]->first; p!=NULL; p=p->next)//duyệt qua danh sách hóa đơn của nhân viên
            if(p->info.thoigian.nam == year)
                thang[p->info.thoigian.thang] += p->info.ptr->total;

    //display
    gotoxy(col, row);
    cout << "THANG |";
    gotoxy(col+8, row);
    cout << "DOANH THU";
    gotoxy(col, row+1);
    for(int j=0; j<21; j++)
    {
        if(j == 6)
            cout << char(197);
        else
            cout << char(196);
    }
    int i=1;
    for(; i<=12; i++)
    {
        gotoxy(col+2, row+1+i);
        cout << i;
        gotoxy(col+6, row+1+i);
        cout <<"| "<<thang[i];
    }
    delete(thang);
    return i;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void Normal()//ham set gia tri mac dinh cho phong chu
{
    SetColor(WHITE);
	SetBGColor(BLACK);
}

void highlight()
{
    SetColor(BLACK);
    SetBGColor(LIGHTER_GRAY);
}

void highlight2()
{
    SetColor(WHITE);
    SetBGColor(RED);
}

void highlight3()
{
    SetColor(WHITE);
    SetBGColor(GREEN);
}

int MENU_DONG_DOC(char menu[DEFAULT_ITEM][DEFAULT_COL], int item, int col, int row, bool left_on, bool right_on, int gap, int color, int bgcolor, int choose)
{
    int dist = choose*2;
    for(int i = 0; i < item; i++)
    {
        Normal();
        gotoxy(col, row + i*gap);
        cout << menu[i];
    }
    SetColor(color); SetBGColor(bgcolor);
    gotoxy(col, row+choose*2);
    cout << menu[choose];
    Normal();
    int banphim;
    do
    {
        banphim = getch();
        if(banphim == 0) banphim = getch();
        switch(banphim)
        {
        case DOWN:if(choose+1 < item){
                gotoxy(col, row+dist); Normal();
                cout << menu[choose]; choose++; dist+=gap;
                gotoxy(col, row+dist); SetColor(color);SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case UP:if(choose > 0){
                gotoxy(col, row+dist); Normal();
                cout << menu[choose]; choose--; dist-=gap;
                gotoxy(col, row+dist); SetColor(color);SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case ENTER:
                gotoxy(col, row+dist);
                Normal();
                cout << menu[choose];
                return choose+1;
        }
        if(left_on)
            switch(banphim){
                case LEFT:
                    gotoxy(col, row+dist);
                    Normal();
                    cout << menu[choose];
                    return -1;
                }
        if(right_on)
            switch(banphim){
                case RIGHT:
                    gotoxy(col, row+dist);
                    Normal();
                    cout << menu[choose];
                    return 0;
                }
    }
    while(true);
}

int MENU_DONG_DOC_FOR_NUMBER(int* menu, int item, int col, int row, int gap, int color, int bgcolor, int choose)
{
    int dist = choose*2;
    if(item == 0) return 0;
    for(int i = 0; i < item; i++)
    {
        Normal();
        gotoxy(col, row + i*gap);
        cout << menu[i];
    }
    gotoxy(0, 0);//đi lên đầu
    SetColor(color); SetBGColor(bgcolor);
    gotoxy(col, row+choose*2);
    cout << menu[choose];
    Normal();
    int banphim;
    do
    {
        banphim = getch();
        if(banphim == 0) banphim = getch();
        switch(banphim)
        {
        case DOWN:if(choose+1 < item){
                gotoxy(col, row+dist); Normal();
                cout << menu[choose]; choose++; dist+=gap;
                gotoxy(col, row+dist); SetColor(color);SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case UP:if(choose > 0){
                gotoxy(col, row+dist); Normal();
                cout << menu[choose]; choose--; dist-=gap;
                gotoxy(col, row+dist); SetColor(color);SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case ENTER:
                gotoxy(col, row+dist);
                Normal();
                cout << menu[choose];
                return menu[choose];
        case ESCAPE:
                gotoxy(col, row+dist);
                Normal();
                cout << menu[choose];
                return -1;
        }
    }
    while(true);
}

int* MENU_DONG_DOC_FOR_NUMBER_v2(int* menu, int item, int col, int row, int color, int bgcolor)
{
    int choose = 0;
    int *flag = new int[item]{0};
    bool swit = OFF;
    for(int i = 0; i < item; i++)
    {
        Normal();
        gotoxy(col, row + i);
        cout << menu[i];
    }
    gotoxy(0, 0);//đi lên đầu
    SetColor(color);
    SetBGColor(bgcolor);
    gotoxy(col, row+choose);
    cout << menu[choose];
    Normal();
    int banphim;
    do
    {
        banphim = getch();
        if(banphim == 0) banphim = getch();
        switch(banphim)
        {
        case DOWN:if(choose+1 < item){
                gotoxy(col, row+choose);
                Normal();
                cout << menu[choose];
                choose++;
                gotoxy(col, row+choose);
                SetColor(color);
                SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case UP:if(choose > 0){
                gotoxy(col, row+choose);
                Normal();
                cout << menu[choose];
                choose--;
                gotoxy(col, row+choose);
                SetColor(color);
                SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case ENTER:
            if(flag[choose] == 0){
                gotoxy(col-3, row+choose);
                SetBGColor(GREEN);
                cout << "  ";
                flag[choose] = menu[choose];
                break;
            }
            else
            {
                gotoxy(col-3, row+choose);
                SetBGColor(BLACK);
                cout << "  ";
                flag[choose] = 0;
                break;
            }
        case CTRL_A:
            if(!swit)
                for(int i=0; i<item; i++)
                {
                    gotoxy(col-3, row+i);
                    SetBGColor(GREEN);
                    cout << "  ";
                    flag[i] = menu[i];
                    swit = ON;
                }
            else
                for(int j=0; j<item; j++)
                {
                    gotoxy(col-3, row+j);
                    SetBGColor(BLACK);
                    cout << "  ";
                    flag[j] = 0;
                    swit = OFF;
                }
            gotoxy(0, 0);//đi lên đầu
            break;
        case ESCAPE:
            gotoxy(col, row+choose);
            Normal();
            cout << menu[choose];
            return flag;
        }
    }
    while(true);
}

int MENU_DONG_NGANG(char menu[DEFAULT_ITEM][DEFAULT_COL], int item, int col, int row, int gap, bool escape, bool up_down, int color, int bgcolor, int choose)
{
    for(int i = 0; i < item; i++)
    {
        gotoxy(col+i*gap, row);
        cout << menu[i];
    }
    gotoxy(col+choose*gap, row);
    SetColor(color); SetBGColor(bgcolor);
    cout << menu[choose];
    int banphim;
    do
    {
        banphim = getch();
        if(banphim == 0) banphim = getch();
        switch(banphim)
        {
        case RIGHT:if(choose+1 < item){
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose]; choose++;
                gotoxy(col+choose*gap, row);
                SetColor(color); SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case LEFT:if(choose > 0){
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose]; choose--;
                gotoxy(col+choose*gap, row);
                SetColor(color); SetBGColor(bgcolor);
                cout << menu[choose];
                }
                break;
        case ENTER:
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose];
                return ++choose;
        case ESCAPE:if(escape){
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose];
                return ESCAPE;
                }
        case DOWN: if(up_down){
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose];
                return -1;
                }
                break;
        case UP: if(up_down){
                gotoxy(col+choose*gap, row);
                Normal();
                cout << menu[choose];
                return 0;
                }
                break;
        }
    }
    while(true);

}

void FRAME(int color, int col, int row, int height, int width)//ham tao khung
{
    SetBGColor(color);
    for(int i=0; i<width; i++)
    {
        gotoxy(col, row+i);
        for(int j=0; j<height; j++)
            cout <<" ";
    }
    Normal();
}

void DELCOLOR(int col, int row, int width, int height)//ham xoa khung
{
    Normal();
    for(int i=0; i<height; i++){
        gotoxy(col, row+i);
        for(int j=0; j<width; j++)
            cout <<" ";
    }
}

void resize_window(int x, int y, int width, int height)//ham chinh sua khung window
{
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd, x, y, width, height,TRUE);
}

void random_word(char* arr, int MAX)//khởi tạo từ random cho dãy arr
{
    char character[26];
    for(int i=97, j=0; j<26; i++, j++)//initialize for character array
        if(j>20) character[j] = ' ';
        else character[j] = i;
    for(int z=0; z<MAX-1; z++)
        arr[z] = character[rand()%26];
    arr[MAX-1] = NULL;
}

void POP_UP(int col, int row, int col_back, int row_back, int del_part, int warn_switch, int minimum)//ham tao tin nhan canh bao
{
    gotoxy(col, row);
    SetColor(YELLOW);
    SetBGColor(RED);
    if(warn_switch == 1) cout << "\aPHAI CO IT NHAT "<< minimum <<" KY TU CHU";
    else if(warn_switch == 2) cout << "\aKHONG DUOC TRUY CAP";
    else if(warn_switch == 3) cout << "\aCHUA CO DATA DE CHINH SUA";
    else if(warn_switch == 4) {Normal(); SetColor(WHITE); SetBGColor(GREEN); cout << "\aTAO DEMO THANH CONG";}
    else if(warn_switch == 5) cout << "\aSOME FIELDS ARE MISSING";
    else if(warn_switch == 6) cout << "\aKHONG TIM THAY FILE";
    else if(warn_switch == 7) cout << "\aREACH MAX -> KHONG DUOC THEM";
    else if(warn_switch == 8) cout << "\aCON VAT TU TRONG DU LIEU";
    else if(warn_switch == 9) {Normal(); SetColor(WHITE); SetBGColor(GREEN); cout << "\aLOAD FILE THANH CONG";}
    else if(warn_switch == 10) cout << "\aKO TIM THAY NHAN VIEN";
    else if(warn_switch == 11) cout << "\aKO TIM THAY VAT TU";
    else if(warn_switch == 12) cout << "\aKO THE XUAT, SO LUONG";
    else if(warn_switch == 13) cout << "\aINVALID";
    else if(warn_switch == 14) cout << "\aCHUA CO DU LIEU VAT TU";
    else if(warn_switch == 15) cout << "\aCHUA CO DU LIEU NHAN VIEN";
    else if(warn_switch == 16) {Normal(); SetColor(WHITE); SetBGColor(GREEN); cout << "\aTAO HOA DON THANH CONG";}
    else if(warn_switch == 17) {Normal(); SetColor(WHITE); SetBGColor(GREEN); cout << "\aSAVE FILE THANH CONG";}
    Sleep(2000);
    DELCOLOR(col, row, 40, 1);
    DELCOLOR(col_back, row_back, del_part, 1);
    gotoxy(col_back, row_back);
}

void preFram(int fram, bool display)//ham tao khung mac dinh cho chuong trinh
{
    if(fram == MODE_0)
    {
        clrscr();
        resize_window(550, 200, 400, 445);
        FRAME(1, 0, 0, 50, 6);
        highlight();
        gotoxy(12, 2);
        cout << " CHUONG TRINH QUAN LI VAT TU ";
        Normal();
    }
    else if(fram == MODE_1)
    {
        if(display)clrscr();
        resize_window(300, 200, 1000, 600);
        FRAME(BLUE, 50, 1, 30, 3);
        highlight();
        gotoxy(50+5, 1+1);
        cout << " THONG TIN VAT TU ";
        FRAME(BLUE, 10, 5, 50, 8);
        FRAME(BLACK, 10+15, 5+1, 30, 1);
        FRAME(BLACK, 10+15, 5+3, 10, 1);
        FRAME(BLACK, 10+15, 5+5, 30, 1);
        for(int i=0; i<3; i++){
            gotoxy(10+1, 5+1+2*i);
            cout << ttvt_menu[i];
        }
        gotoxy(62, 5);
        cout << save_menu[0];
        gotoxy(62, 5+2);
        cout << save_menu[1];
    }
    else if(fram == MODE_2)
    {
        clrscr();
        resize_window(300, 200, 1000, 600);
        FRAME(BLUE, 50, 1, 30, 3);
        highlight();
        gotoxy(50+5, 1+1);
        cout << " QUAN LY NHAN VIEN ";
        FRAME(BLUE, 10, 5, 50, 7);
        FRAME(BLACK, 10+11, 5+1, 30, 1);
        FRAME(BLACK, 10+11, 5+3, 30, 1);
        int i=0;
        for(; i<4; i++){
            gotoxy(10+1, 5+1+2*i);
            cout << nvinfo_menu[i];
        }
        for(i=0; i<2; i++){
            gotoxy(10+13+12*i, 5+5);
            cout << sex_menu[i];
        }
    }
    else if(fram == MODE_3 || fram == MODE_4)
    {
        gotoxy(62, 5);
        cout << save_menu[0];
        gotoxy(62, 5+2);
        cout << save_menu[1];
        if(fram == MODE_4){
            gotoxy(62, 5+4);
            cout << save_menu[2];
        }
    }
    else if(fram == MODE_5)
    {
        clrscr();
        resize_window(200, 50, 1200, 750);
        FRAME(BLUE, 65, 1, 25, 3);
        highlight();
        gotoxy(65+5, 1+1);
        cout << " TAO HOA DON ";

        FRAME(BLUE, 10-8, 5, 48, 9);
        FRAME(BLACK, 10+14-8, 5+1, 3, 1);
        FRAME(BLACK, 10+14-8, 5+3, 1, 1);
        gotoxy(10+1-8, 5+1); cout << hd_menu[0];
        gotoxy(10+1-8, 5+3); cout << hd_menu[1];
        gotoxy(10+48+1-8, 5); cout << save_menu[0];
        gotoxy(10+48+1-8, 7); cout << save_menu[1];

        FRAME(BLUE, 65, 5, 30, 11);
        FRAME(BLACK, 65+13, 5+1, 10, 1);
        FRAME(BLACK, 65+13, 5+3, 10, 1);
        FRAME(BLACK, 65+13, 5+5, 10, 1);
        FRAME(BLACK, 65+13, 5+7, 10, 1);
        for(int i=0; i < item_cthd; i++){
            gotoxy(65+1, 5+1+2*i);
            cout << cthd_menu[i];
        }
        gotoxy(65+30+1, 5); cout << save_menu[0];
        gotoxy(65+30+1, 7); cout << save_menu[1];
        gotoxy(65+30+1, 9); cout << save_menu[2];

    }
    else if(fram == MODE_6)
    {
        clrscr();
        resize_window(300, 200, 1000, 600);
        FRAME(BLUE, 50, 1, 20, 3);
        highlight();
        gotoxy(50+5, 1+1);
        cout << " THONG KE ";
        Normal();

        for(int i=0; i<4; i++)
        {
            gotoxy(1, 5+i*2);
            cout << thongke_menu[i];
        }

    }
    else if(fram == MODE_7)
    {
        gotoxy(30, 5);
        cout << "BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
    }
    else if(fram == MODE_8)
    {
        gotoxy(50, 5);
        cout << "TOP 10 VAT TU";
    }
    else if(fram == MODE_9)
    {
        gotoxy(30, 5);
        cout << "BANG THONG KE DOANH THU NAM:";
    }
    else if(fram == MODE_10)
    {
        clrscr();                       //
        FRAME(BLUE, 50, 1, 30, 3);      //
        instruct(85, 8, "DELETE");      //
        highlight();                    //hiển thị giao diện
        gotoxy(50+5, 1+1);              //
        cout << " THONG TIN VAT TU ";   //
        Normal();
    }
    else if(fram == MODE_11)
    {
        clrscr();
        FRAME(BLUE, 50, 1, 30, 3);
        highlight();
        gotoxy(50+5, 1+1);
        cout << " QUAN LY NHAN VIEN ";
        Normal();
    }
}

bool exitpop(int col, int row,int asked)//ham tao khung tin nhan ->hoi xem la co muon luu hay ko
{
    FRAME(RED, col, row, 26, 7);
    FRAME(BLUE, col+2, row+1, 25-3, 7-2); // subframe
    gotoxy(col+8, row+2);
    SetBGColor(BLACK); SetColor(WHITE);
    if(asked == 0) cout << "EXIT?";
    else if(asked == 1) cout << "SAVE All?";
    else if(asked == 2) cout << "SAVE?";
    else if(asked == 3) cout << "SURE?";
    char menu[2][DEFAULT_COL] = {"YES", "NO"};
    int opt = MENU_DONG_NGANG(menu, 2, col+6, row+4, 12, OFF, OFF, BLACK, WHITE);
    switch(opt){
        case 1:
            DELCOLOR(col, row, 26, 7);
            return true; break;
        case 2:
            DELCOLOR(col, row, 26, 7);
            return false; break;
        }
}

void nhapChu(char* arr, int MAX, int col, int row, bool swit)//ham nhap chu vao trong chuoi
{
    gotoxy(col, row);
    int col_pos = col, i = 0;
    while(arr[i] = getch()){
        if(arr[i] == 8 && i>0)//backspace
        {
            i--;
            arr[i] = NULL;
            gotoxy(col_pos-1, row);
            cout << " ";
            gotoxy(col_pos-1, row);
            col_pos = col_pos-1;
            continue;
        }
        else if(arr[i] == 13 || arr[i] == 27)//enter
        {
            if(arr[i] == 27) i=0;
            for(;i < MAX; i++)
                arr[i] = NULL;
            break;
        }
        if(i == MAX-1) continue;//
        if((arr[i] >= 97 && arr[i] <= 122) || arr[i]==' ' || (arr[i] >= 30 && arr[i] <= 39))//condition
        {
            cout << arr[i];
            col_pos++;
            i++;
        }
        if(arr[i] >= 48 && arr[i] <= 57 && swit)
        {
            cout << arr[i];
            col_pos++;
            i++;
        }
    }
}

void namefilter(char* arr)//hàm lọc ký tự trắng cho chuỗi
{
    int switchcount =0;
    bool swit1 = false;
    for(int i=0, j=0;; i++)
    {
        if(arr[i] == NULL)//exit
        {
            arr[j] = NULL;
            if(arr[j-1] == ' ') arr[j-1] = NULL;
            if(j==i) break;
            j++;
            --i;
            continue;
        }
        if(arr[i] != ' ')
            swit1 = true;
        if(swit1)
        {
            arr[j] = arr[i];
            j++;
            swit1 = false;
            switchcount++;
        }
        if(switchcount > 0 && arr[i] == ' ')
        {
            arr[j] = ' ';
            j++;
            switchcount=0;
        }
    }
}

int nhapSo(int MAX, int col, int row)//ham nhap so vao chuoi ->sinh ra ma vat tu, ma nhan vien
{
    gotoxy(col, row);
    char digit_arr[MAX+1];
    int cursor = col, i=0;
    while(digit_arr[i] = getch())
    {
        if(digit_arr[i] == 8 && i>0)//backspace
        {
            i--;
            digit_arr[i] = NULL;
            gotoxy(cursor-1, row);
            cout << " ";
            gotoxy(cursor-1, row);
            cursor--;
            continue;
        }
        else if(digit_arr[i] == 13 || digit_arr[i] == 27)//enter
        {
            if(digit_arr[i] == 27) i=0;
            for(;i<=MAX;i++)
                digit_arr[i] = NULL;
            break;
        }
        if(i == MAX) continue;//limit input
        if(digit_arr[i] >= 48 && digit_arr[i] <= 57)//condition
        {
            cout << digit_arr[i];
            cursor++;
            i++;
        }
    }
    return numConvert_reverse(digit_arr);
}

int numConvert_reverse(char *arr)//hàm chuyển từ số kiểu char sang số kiểu int
{
    int result = 0, MAX = 0;
    bool swit = true;//count how many digit in the arr
    for(int i=0; i <= MAX; i++)
    {
        if(arr[i]!=NULL && swit)
            ++MAX;
        else if(swit)
        {
            swit = false;
            --MAX;
            i=0;
        }
        if(!swit)
            if(arr[i] >= 48 && arr[i] <= 57)
                result += (arr[i]-48)*power(10, MAX-i);
            else return -1;
    }
    return result;
}

int power(int coso, int mu)//hàm mũ
{
    if(coso == 0) return 0;
    else if(coso == 1) return 1;
    else if(mu == 0) return 1;
    else if(mu == 1) return coso;
    int result=1;
    for(int i=1; i<=mu; i++)
        result *= coso;
    return result;
}

void numConvert(int num, char* arr, int MAX)// ham chuyen kieu int sang char array theo format
{
    for(int k=MAX-1; k>=0; k--)
        if(k == MAX-1) arr[k] = NULL;
        else arr[k] = 48;//0
    for(int i=num, z=MAX-2; i>0 ; i/=10, z--){
        if(i<10)
        {
            arr[z] = i+48;
        }
        for(int j=0; j<=9; j++)
            if((i-j)%10==0)
            {
                arr[z] = j+48;
                i-=j;
                j=0;
                break;
            }
    }
}

int arrCopy(char *arr1, int a1_index, char *arr2)
{
    int i=0, j=a1_index;
    for(; arr2[i]!=NULL; i++, j++)
        arr1[j] = arr2[i];
    return i;
}

void arrCopy_v2(char *arr1, char *arr2, int maxa2)
{
    for(int i=0; i<maxa2; i++)
        arr1[i] = arr2[i];
}

int strComp(char *left, char *right)//check xem 2 chuỗi có trùng nhau (hàm chỉ so sánh ký tự chữ bỏ qua ký tự trắng)
{
    int i=0, j=0;
    while(true)
    {
        if(left[i] != char(32))
        {
            if(right[j] != char(32))
            {
                if(left[i] == right[j])
                {
                    i++;
                    j++;
                }
                else if(left[i] > right[j])
                    return 1;//left lớn hơn right
                else
                    return -1;//left bé hơn right
            }
            else j++;
        }
        else i++;
        if(left[i] == NULL && right[j] == NULL) return 0;//left bằng right
    }
}

void instruct(int col, int row, const char* menu)//hàm hiển thị hướng dẫn
{
    FRAME(GRAY, col, row-1, 11, 11);
    char guide[7][DEFAULT_COL] = {"LEFT", "RIGHT", "UP", "DOWN", "ENTER", "ESC", "Crtl+A: SELECT ALL"};
    if(menu == "MENU")
    {
        for(int i=0; i<3; i++)
        {
            gotoxy(col+1, row+i*2);
            cout << guide[i+2];
        }
    }
    else if(menu == "INFO")
    {
        for(int i=0; i<5; i++)
        {
            gotoxy(col+1, row+i*2);
            cout << guide[i];
        }
    }
    else if(menu == "MODIFY")
    {
        for(int i=0; i<4; i++)
        {
            gotoxy(col+1, row+i*2);
            cout << guide[i+2];
        }
        cout << ": exit";
    }
    else if(menu == "DELETE")
    {
        FRAME(GRAY, col+11, row-1, 11, 11);
        gotoxy(col+1, row+1); cout << guide[2];
        gotoxy(col+1, row+3); cout << guide[3];
        gotoxy(col+1, row+5); cout << guide[5] << ": Execute or exit";
        gotoxy(col+1, row+7); cout << guide[6];
    }
    else if(menu == "TK")
    {
        gotoxy(col+1, row+1); cout << guide[0];
        gotoxy(col+1, row+3); cout << guide[1];
        gotoxy(col+1, row+5); cout << guide[4];
        gotoxy(col+1, row+7); cout << guide[5];
    }
    else if(menu == "ENTER")
    {
        gotoxy(col+1, row+1); cout << guide[4];
        gotoxy(col+1, row+3); cout << "'0': exit";
    }
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void saveInfoVT(VTPTR &root, KPTR &keyArr)//lưu tất cả thông tin vật tư trong tree
{
    mkdir("thong tin quan li");
    FILE *ptr = fopen("thong tin quan li/dsvt.txt", "w");
    if(ptr == NULL)
    {
        cout << "KO MO DC FILE" << endl;
        return;
    }
    VATTU info;
    for(KPTR p = keyArr; p != NULL; p = p->next)
    {
        info = searchTree(root, p->key);
        fprintf(ptr, "%s,%s,%s,%d\n", info.mavt, info.tenvt, info.don_vi_tinh, info.soluongton);
    }
    fclose(ptr);
}

void loadFileVT(VTPTR &root, KPTR &keyArr)//hàm load file
{
    FILE *ptr = fopen("thong tin quan li/dsvt.txt", "r");
    if(ptr == NULL)
    {
        POP_UP(13, 18, 13, 19, 10, MODE_6);
        return;
    }
    VATTU info;
    do
    {
        int read = fscanf(ptr, "%10[^,],%20[^,],%5[^,],%d\n", info.mavt, info.tenvt, info.don_vi_tinh, &info.soluongton);
        if(read == 0)
        {
            cout << "ko doc dc zi" ;
            fclose(ptr);
            return;
        }
        int key = numConvert_reverse(info.mavt);
        root = insertTree(root, key, info);
        insert_Key(keyArr, initKey(key, info.tenvt, OFF));
    }
    while(!feof(ptr));
    fclose(ptr);
}

void filenameCre(int manv, char *fname)
{
    int num = 25;
    fname[num] = fname[num-1] = fname[num-2] = '0';
    while(true)
    {
        if(manv<10)break;
        int i=0;
        while(i<=9)
        {
            if((manv-i)%10==0) break;
            i++;
        }
        fname[num] = char(i+48);
        manv = (manv-i)/10;
        num--;
    }
    fname[num] = char(manv+48);
}

void saveInfoNV(Listnv &ds)
{
    mkdir("thong tin quan li/dsnv");
    char fname[31] = "thong tin quan li/dsnv/000.txt";
    FILE *ptr;
    NHANVIEN tempnv;
    dshd temphd;
    DS_CTHD tempdscthd;
    chitietHD tempcthd;
    for(int i=0; i<ds.n; i++)
    {
        if(ds.nvnode[i]->state == '1');
        {
            filenameCre(ds.nvnode[i]->manv, fname);
            ptr = fopen(fname, "w");
            if(ptr == NULL)
            {
                cout << "nope";
                return;
            }
            tempnv = *ds.nvnode[i];
            fprintf(ptr, "%d,%s,%s,%c\n",
                    tempnv.manv,
                    tempnv.ten,
                    tempnv.hoten,
                    tempnv.gioitinh);
            for(PTRHD p = tempnv.first; p!=NULL; p=p->next)
            {
                temphd = p->info;
                fprintf(ptr, "%s,%d,%d,%d,%d,%d,%c\n",
                        temphd.soHD,
                        temphd.thoigian.ngay,
                        temphd.thoigian.thang,
                        temphd.thoigian.nam,
                        temphd.thoigian.gio,
                        temphd.thoigian.phut,
                        temphd.loai);
                tempdscthd = *temphd.ptr;
                for(int z=0; z<tempdscthd.n; z++)
                {
                    tempcthd = *(tempdscthd.cthd[z]);
                    fprintf(ptr, "%s,%s,%d,%d,%f\n",
                            tempcthd.mactvt,
                            tempcthd.tenctvt,
                            tempcthd.soluong,
                            tempcthd.dongia,
                            tempcthd.vat);
                }
            }
            fclose(ptr);
        }
    }
}

int getsoCTHD(char *soHD)
{
    char buffer[8];
    for(int i=0; i<8; i++)
        buffer[i] = soHD[i+12];
    return numConvert_reverse(buffer);
}

void loadFileNV(Listnv &ds)
{
    char fname[31] = "thong tin quan li/dsnv/000.txt";
    dshd temphd;
    chitietHD *tempcthd;
    NHANVIEN *nv;
    FILE *ptr;
    int check;
    for(int i=1; i<=MAXNV; i++)
    {
        filenameCre(i, fname);
        ptr = fopen(fname, "r");

        if(ptr != NULL)
        {
            ds.nvnode[ds.n] = new NHANVIEN;
            nv = ds.nvnode[ds.n];
            nv->state = '0';
            fscanf(ptr, "%d,%9[^,],%29[^,],%c\n", &nv->manv, nv->ten, nv->hoten, &nv->gioitinh);
            do
            {
                fscanf(ptr, "%19[^,],%d,%d,%d,%d,%d,%c\n",
                        temphd.soHD,
                        &temphd.thoigian.ngay,
                        &temphd.thoigian.thang,
                        &temphd.thoigian.nam,
                        &temphd.thoigian.gio,
                        &temphd.thoigian.phut,
                        &temphd.loai);
                temphd.ptr = new DS_CTHD;
                check = getsoCTHD(temphd.soHD);
                for(int j=0; j<check; j++)
                {
                    temphd.ptr->cthd[temphd.ptr->n] = new chitietHD;
                    tempcthd = temphd.ptr->cthd[temphd.ptr->n];
                    fscanf(ptr, "%9[^,],%19[^,],%d,%d,%f\n",
                            tempcthd->mactvt,
                            tempcthd->tenctvt,
                            &tempcthd->soluong,
                            &tempcthd->dongia,
                            &tempcthd->vat);
                    temphd.ptr->n++;
                }
                addHD(temphd, ds, ds.n);
            }
            while(!feof(ptr));
            fclose(ptr);
            ds.n++;
        }
    }

}

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////DEMO FUNCTION///////////////////////////////////////////
DS_CTHD cthdDemo(VTPTR &dsvt, KPTR &keyArr)
{
    VATTU tempvt;
    DS_CTHD temp;
    chitietHD *p;
    date tempd;
    int key, sum, num;
    int* mavt = convert_keyArr(keyArr, OFF, num);
    temp.n = rand()%10+10;
    for(int i=0; i<temp.n; i++)
    {
        temp.cthd[i] = new chitietHD;
        p = temp.cthd[i];
        p->dongia = rand()%20000;
        p->soluong = rand()%5+5;
        p->vat = rand()%5+5;
        sum = p->dongia*p->soluong;
        temp.total += sum + sum*(p->vat/100);
        key = mavt[rand()%(num-1)];
        tempvt = searchTree(dsvt, key);
        numConvert(key, p->mactvt, 10);
        arrCopy(p->tenctvt, 0, tempvt.tenvt);
        p->tenctvt[19] = NULL;
    }
    return temp;
}

void dshdDemo(Listnv &dsnv, VTPTR &dsvt, KPTR &keyArr, int nvindex)
{
    dshd temphd;
    int SLHD = rand()%10+10;
    for(int j=0; j<=SLHD; j++)
    {
        now.ngay--;
        if(now.ngay == 0)
        {
            now.ngay = 30;
            now.thang--;
            if(now.thang == 0)
            {
                now.thang = 12;
                now.nam--;
            }
        }
    }
    date time = now;
    for(int i=0; i<=SLHD; i++)
    {
        if((rand()%9+1) > 5) temphd.loai = 'X';//khỏi tạo giá trị cho loai HD
        else temphd.loai = 'N';

        temphd.ptr = new DS_CTHD{cthdDemo(dsvt, keyArr)};//khởi tạo giá trị cho DS_CTHD

        temphd.thoigian = time;
        time.ngay++;
        if(time.ngay == 31)
        {
            time.ngay = 1;
            time.thang++;
            if(time.thang == 13)
            {
                time.thang = 1;
                time.nam++;
            }
        }
        mahdGen(temphd.soHD, dsnv.nvnode[nvindex]->manv, temphd.thoigian, temphd.loai, temphd.ptr->n);
        addHD(temphd, dsnv, nvindex);
    }
}

void creDemo(VTPTR &dsvt, Listnv &ds, KPTR &keyArr)//hàm tạo ra thông tin vt giả để test chương trình
{
    if(dsvt != NULL && ds.n != 0)
    {
        POP_UP(13, 18, 13, 19, 0, MODE_8);
        return;
    }
    gotoxy(13, 18); cout << "Loading";
    if(dsvt == NULL)
    {
        VATTU infovt;
        int key;
        for(int i=1; i<=30; i++)
        {
            random_word(infovt.tenvt, 20);//tạo mã giả cho tên vt
            namefilter(infovt.tenvt);//hàm filter cho tên vt
            random_word(infovt.don_vi_tinh, 5);//tạo mã giả cho đơn vị tính
            namefilter(infovt.don_vi_tinh);//filter cho đơn vị tính

            key = keyGen(keyArr, infovt.tenvt, ON);//tạo khóa va luu vao chuoi keyArr
            numConvert(key, infovt.mavt, 10);//tạo mã vt từ key

            infovt.soluongton = rand()%1000+1000;//tạo số giả cho số lượng tồn
            dsvt = insertTree(dsvt, key, infovt);// đưa info vào tree p qua khóa key
        }
    }
    if(ds.n == 0)
    {
        NHANVIEN *infonv = new NHANVIEN;
        for(int j=0; j<10; j++)
        {
            infonv->manv = j+1;
            infonv->state = '1';
            random_word(infonv->hoten, 30);
            namefilter(infonv->hoten);
            random_word(infonv->ten, 10);
            namefilter(infonv->ten);
            infonv->gioitinh = '2';
            ds.nvnode[ds.n] = infonv;
            ds.n++;
            infonv = new NHANVIEN;
        }
        relocNV(ds);
        for(int j=0; j<10; j++)
            dshdDemo(ds, dsvt, keyArr, j);
    }
    POP_UP(13, 18, 13, 19, 0, MODE_4);
}
////////////////////////////////////////////////////////////////////////////////
