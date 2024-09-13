#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>

struct Date {
	int day;
	int month;
	int year;
};

typedef struct Student
{
	long long ID;	                /* Mã số sinh viên */
	char name[25];            	    /* Tên sinh viên */
    Date date_of_birth;             /* Ngày sinh */
    char from[20];                  /* Quê quán của sinh viên */
    char Class[20];                 /* Mã lớp sinh viên*/
	float GPA;						/* Điểm trung bình của mỗi sinh viên */
}STU;

struct node {                       /* Xây dựng 1 node chứa thông tin của 1 sinh viên */
	STU student;
	node *next;
};

/* Xây dựng 1 danh sách chứa thông tin các sinh viên */
struct list {                       
    node *head;
    node *tail;
};

node *getNode(STU student);                           /* Đưa thông tin của 1 sinh viên vào 1 node */
void initList(list &l);                               /* Khởi tạo danh sách trống */
bool isEmpty(list l);                                 /* Kiểm tra danh sách có rỗng không */
bool check_duplicate_ID(list, long long ID);          /* Hàm kiểm tra MSSV bị trùng */ 
bool isLeapYear(int year);                            /* Hàm kiểm tra năm nhuận */
bool isValidDate(int day, int month, int year);       /* Hàm kiểm tra ngày tháng năm hợp lệ */
void addTail(list &l, node *new_node);                /* Thêm 1 node (sinh viên) mới vào cuối danh sách */
int SizeOfList(list l);                               /* Đếm số phần tử (sinh viên) trong danh sách */
void RemoveNode(list &l, long long ID);               /* xóa node khỏi danh sách liên kết */
void sort_by_ID(list &l);                             /* Hàm sắp xếp sinh viên theo MSSV */
void searchStudentByName(list l, char x[]);           /* Hàm tra cứu thông tin sinh viên theo tên */
void changed(list &l, long long ID);                  /* Hàm thay đổi thông tin sinh viên */
void write_to_file(list l);                           /* Hàm ghi dữ liệu sinh viên vào file */
void read_from_file(list &l, STU student);            /* Hàm đọc dữ liệu sinh viên từ file */
void import(list &l, STU student);                    /* Hàm nhập thông tin 1 sinh viên và đưa vào danh sách liên kết đơn*/
void Export(list l);                                  /* Hàm xuất danh sách sinh viên ra màn hình */
void SET_COLOR(int color)
{
	WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
    }
}

int main() {
	list Students;
	initList(Students);

	SET_COLOR(10);
	printf("\n===================== M E N U ========================");
	printf("\n| 0  | Xuat danh sach sinh vien                      |");
	printf("\n| 1  | Them sinh vien                                |");
    printf("\n| 2  | Xoa sinh vien                                 |");
	printf("\n| 3  | Thay doi thong tin sinh vien                  |");
	printf("\n| 4  | Tra cuu thong tin sinh vien theo ten          |");
	printf("\n| 5  | Sap xep sinh vien theo ma so sinh vien        |");
	printf("\n| 6  | Dem so luong sinh vien trong danh sach        |");
	printf("\n| 7  | Ghi du lieu sinh vien vao file                |");
	printf("\n| 8  | Doc du lieu sinh vien tu file                 |");
	printf("\n| 9  | Xoa man hinh                                  |");
	printf("\n| 10 | Thoat chuong trinh                            |");
	printf("\n======================================================");

	while(true) {
		SET_COLOR(7);
		int choice;
		printf("\nVui long nhap lua chon cua ban: ");
		do {
			scanf("%d", &choice); getchar();
			if(choice < 0 || choice > 10) 
				printf("Lua chon khong hop le, vui long nhap lai: ");
		} while(choice < 0 || choice > 10);

		switch(choice) {
			case 0:
				SET_COLOR(14);
				Export(Students);
				break;
			case 1: 
				STU st1;
				import(Students, st1);
				break;
			case 2: {
				long long ID;
				printf("Nhap MSSV cua sinh vien can xoa: ");
				scanf("%lld", &ID);
				RemoveNode(Students, ID);
				break;
			}
			case 3: {
				long long ID; printf("Nhap MSSV cua sinh vien can thay doi thong tin: ");
				scanf("%lld", &ID); getchar();
				changed(Students, ID);
				break;
			}
			case 4:
				char name[25];
				printf("Nhap ten sinh vien can tra cuu thong tin: ");
				fgets(name, sizeof(name), stdin);
				name[strcspn(name, "\n")] = '\0';
				searchStudentByName(Students, name);
				break;
			case 5: 
				sort_by_ID(Students);
				break;
			case 6:
				printf("Danh sach co %d sinh vien !", SizeOfList(Students));
				break;
			case 7: 
				write_to_file(Students);
				break;
			case 8: 
				STU st2;
				read_from_file(Students, st2);
				break;
			case 9:
				system("cls");
			 	break;
			case 10:
				printf("Cam on da su dung chuong trinh, hen gap lai <3 !");
				return 0;
		}
	}
}

/* Đưa thông tin của 1 sinh viên vào 1 node */
node *getNode(STU student) {        
	node *ptr;
	ptr = (node*) malloc(sizeof(node));
	if(ptr == NULL) {
		printf("Khong du bo nho !");
		return NULL;
	}
	ptr->student = student;
	ptr->next = NULL;
	return ptr;
}

/* Khởi tạo danh sách trống */
void initList(list &l) {            
    l.head = NULL;
    l.tail = NULL;
}

/* Kiểm tra danh sách có rỗng không */
bool isEmpty(list l) {              
    return l.head == NULL;
}

/* Hàm kiểm tra MSSV bị trùng */ 
bool check_duplicate_ID(list l, long long ID) {
	while(l.head != NULL) {
		if(l.head->student.ID == ID) return true;
		l.head = l.head->next;
	}
	return false;
}

/* Hàm kiểm tra năm nhuận */
bool isLeapYear(int year) {
    // Năm nhuận phải chia hết cho 4, nhưng không được chia hết cho 100 nếu không chia hết cho 400
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/* Hàm kiểm tra ngày tháng năm hợp lệ */
bool isValidDate(int day, int month, int year) {
    // Kiểm tra tháng từ 1 đến 12
    if (month < 1 || month > 12)
        return false;

    // Kiểm tra ngày từ 1 đến 31
    if (day < 1 || day > 31)
        return false;

    // Kiểm tra ngày tháng 2
    if (month == 2) {
        // Nếu là năm nhuận, ngày không quá 29
        if (isLeapYear(year))
            return (day <= 29);
        // Nếu không phải năm nhuận, ngày không quá 28
        else
            return (day <= 28);
    }

    // Kiểm tra tháng có 30 ngày
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);

    // Các tháng còn lại có 31 ngày
    return true;
}

/* Thêm 1 node (sinh viên) mới vào cuối danh sách */
void addTail(list &l, node *new_node) { 
    if(isEmpty(l)) {
        l.head = l.tail = new_node;
    }
    else {
        l.tail->next = new_node;
        l.tail = new_node;
    }
}

/* Đếm số phần tử (sinh viên) trong danh sách */
int SizeOfList(list l) {
    int nSize = 0;
    while(l.head != NULL)
    {
        l.head = l.head->next;
        nSize++;
    }
    return nSize;
}

/* xóa node khỏi danh sách liên kết */
void RemoveNode(list &l, long long ID) { // Hàm xóa sinh viên theo mã số sinh viên
	node *pDel = l.head; // tạo một node pDel để xóa
	//Nếu pDel == Null thì danh sách rỗng
	if(pDel == NULL) {
    	printf("Danh sach rong !");
	}
	//ngược lại thì xét điều kiện
	else {
    	node *pPre = NULL;
    	//dùng vòng lặp while để tìm ra pDel và pPre (vị trí đứng trước pDel)
    	while(pDel != NULL){
    		if(pDel->student.ID == ID) break;
    		pPre = pDel;
    		pDel = pDel -> next;
    	}
    	//Nếu pDel == null tức là không tìm thấy dữ liệu cần xóa
    	if(pDel == NULL)
			printf("Khong tim thay sinh vien can xoa !");
    	// Ngược lại tiếp tục xét điều kiện
    	else {
      		// Nếu pDel == l.head, tức là số cần xóa ở đầu danh sách
      		if(pDel == l.head) {
        		l.head = l.head -> next;
        		pDel -> next = NULL;
        		free (pDel);
        		pDel = NULL;
      		}
      		//Nếu pDel == l.tail, tức là số cần xóa ở cuối danh sách
      		else if(pDel -> next == NULL) {
        		l.tail = pPre;
        		pPre -> next = NULL;
        		free (pDel);
        		pDel = NULL;
      		}
      		// và trường hợp cuối cùng số muốn xóa nằm ở giữa danh sách
      		else {
        		pPre -> next = pDel -> next;
        		pDel -> next = NULL;
        		free (pDel);
        		pDel = NULL; 
      		}
			printf("Xoa sinh vien thanh cong !");
    	}
  	}
}

/* Hàm sắp xếp sinh viên theo MSSV */
void sort_by_ID(list &l) {
	for(node *p = l.head; p != NULL; p = p->next) {
        for(node *q = p->next; q != NULL; q = q->next) {
            if(p->student.ID > q->student.ID) {
                STU temp = p->student;
                p->student = q->student;
                q->student = temp;
            }
        }
    }
    printf("Sap xep thanh cong !");
}

/* Hàm tra cứu thông tin sinh viên theo tên */
void searchStudentByName(list l, char x[]) {
    node *p;
    p = l.head;
    while(p != NULL && strcmp(p->student.name, x) != 0) {
        p = p->next;
    }
	if(p == NULL) printf("Khong ton tai sinh vien %s !", x);
	else {
		printf("Thong tin sinh vien %s:\n", x);
		printf("MSSV: %lld\n", p->student.ID);
		printf("Ho va ten: %s\n", p->student.name);
		printf("Ngay sinh: %s\n", p->student.date_of_birth);
		printf("Dia chi: %s\n", p->student.from);
		printf("Lop: %s\n", p->student.Class);
		printf("GPA: %.2f", p->student.GPA);
	}
}

/* Hàm thay đổi thông tin sinh viên */
void changed(list &l, long long ID) {
	node *pT = l.head;
	if(isEmpty(l)) {
		printf("Danh sach sinh vien trong !");
		return;
	}
	while(pT != NULL) {
		if(pT->student.ID == ID) break;
		pT = pT->next;
	}
	if(pT == NULL) {
		printf("Khong tim thay sinh vien co ma so %lld !", ID);
		return;
	}
	else {
		printf("Hay nhap thong tin can thay doi cua sinh vien co ma so %lld\n", ID);
		printf("MSSV: "); 
		do {
			scanf("%lld", &pT->student.ID); getchar();
			if(check_duplicate_ID(l, ID))
				printf("MSSV da ton tai, vui long nhap lai: ");
		} while(check_duplicate_ID(l, ID));
		
		printf("Ten sinh vien: ");
		fgets(pT->student.name, sizeof(pT->student.name), stdin);
		pT->student.name[strcspn(pT->student.name, "\n")] = '\0';

		printf("Ngay sinh: ");
		do {
		scanf("%d %d %d", &pT->student.date_of_birth.day, &pT->student.date_of_birth.month, &pT->student.date_of_birth.year);
		getchar();
		if(isValidDate(pT->student.date_of_birth.day, pT->student.date_of_birth.month, pT->student.date_of_birth.year) == false)
			printf("Ngay khong hop le, vui long nhap lai: ");
		} while(isValidDate(pT->student.date_of_birth.day, pT->student.date_of_birth.month, pT->student.date_of_birth.year) == false);


		printf("Dia chi: ");
		fgets(pT->student.from, sizeof(pT->student.from), stdin);
		pT->student.from[strcspn(pT->student.from, "\n")] = '\0';

		printf("Ma lop: ");
		fgets(pT->student.Class, sizeof(pT->student.Class), stdin);
		pT->student.Class[strcspn(pT->student.Class, "\n")] = '\0';

		printf("GPA: "); scanf("%f", &pT->student.GPA); getchar();
	}
	printf("Da thay doi thong tin sinh vien co ma so %lld !", ID);
}

/* Hàm ghi dữ liệu sinh viên vào file */
void write_to_file(list l) {
	FILE *fp;
	if((fp = fopen("students.txt", "w")) == NULL) {
		printf("Loi khi mo file student.txt !");
		return;
	}
	while(l.head != NULL) {
		fprintf(fp, "%lld|", l.head->student.ID);
		fprintf(fp, "%s|", l.head->student.name);
		fprintf(fp, "%d|", l.head->student.date_of_birth.day); 
		fprintf(fp, "%d|", l.head->student.date_of_birth.month); 
		fprintf(fp, "%d|", l.head->student.date_of_birth.year); 
		fprintf(fp, "%s|", l.head->student.from); 
		fprintf(fp, "%s|", l.head->student.Class); 
		fprintf(fp, "%.2f\n", l.head->student.GPA);
		l.head = l.head->next;
	}
	fclose(fp);
	printf("Ghi du lieu vao file thanh cong !");
}

/* Hàm đọc dữ liệu sinh viên từ file */
void read_from_file(list &l, STU student) {
    FILE *fp;
    char line[256]; // Đọc mỗi dòng tối đa có 256 ký tự
    if ((fp = fopen("students.txt", "r")) == NULL) {
        printf("Loi khi mo file student.txt !");
        return;
    }
	
    while (fgets(line, sizeof(line), fp)) {
        char *token;
        // Lưu trữ ID
        token = strtok(line, "|");
        sscanf(token, "%lld", &student.ID);

        // Lưu trữ tên
        token = strtok(NULL, "|");
        strcpy(student.name, token);

        // Lưu trữ ngày sinh
        token = strtok(NULL, "|");
        sscanf(token, "%d", &student.date_of_birth.day);

		// Lưu trữ tháng sinh
        token = strtok(NULL, "|");
        sscanf(token, "%d", &student.date_of_birth.month);

		// Lưu trữ năm sinh
        token = strtok(NULL, "|");
        sscanf(token, "%d", &student.date_of_birth.year);

        // Lưu trữ quê quán
        token = strtok(NULL, "|");
        strcpy(student.from, token);

        // Lưu trữ lớp
        token = strtok(NULL, "|");
        strcpy(student.Class, token);

        // Lưu trữ GPA
        token = strtok(NULL, "|");
        sscanf(token, "%f", &student.GPA);

		addTail(l, getNode(student));
    }
    fclose(fp);
    printf("Doc du lieu tu file thanh cong !");
}

/* Hàm nhập thông tin 1 sinh viên và đưa vào danh sách liên kết đơn*/
void import(list &l, STU student) {
	printf("Nhap MSSV: "); 
	do {
		scanf("%lld", &student.ID); getchar();
		if(check_duplicate_ID(l, student.ID))
			printf("MSSV da ton tai, vui long nhap lai: ");
	} while(check_duplicate_ID(l, student.ID));
	
	printf("Nhap ten sinh vien: ");
	fgets(student.name, sizeof(student.name), stdin);
	student.name[strcspn(student.name, "\n")] = '\0';

	printf("Nhap ngay, thang, nam sinh: ");
	do {
		scanf("%d %d %d", &student.date_of_birth.day, &student.date_of_birth.month, &student.date_of_birth.year);
		getchar();
		if(isValidDate(student.date_of_birth.day, student.date_of_birth.month, student.date_of_birth.year) == false)
			printf("Ngay khong hop le, vui long nhap lai: ");
	} while(isValidDate(student.date_of_birth.day, student.date_of_birth.month, student.date_of_birth.year) == false);

	printf("Nhap dia chi: ");
	fgets(student.from, sizeof(student.from), stdin);
	student.from[strcspn(student.from, "\n")] = '\0';

	printf("Nhap ma lop: ");
	fgets(student.Class, sizeof(student.Class), stdin);
	student.Class[strcspn(student.Class, "\n")] = '\0';

	printf("Nhap GPA: "); scanf("%f", &student.GPA); getchar();
	addTail(l, getNode(student));
	printf("Them sinh vien thanh cong !");
}

/* Hàm xuất danh sách sinh viên ra màn hình */
void Export(list l) {
	if(isEmpty(l)) {
        printf("Danh sach trong !");
        return;
    }
	int stt = 0;
    printf("=====================================================================================================================\n");
    printf("| %-5s | %-12s | %-25s | %-13s | %-20s | %-15s | %-5s |", "STT", "MSSV", "Ho Va Ten", "Ngay Sinh", "Dia Chi", "Lop", "GPA");
    printf("\n=====================================================================================================================\n");
    while(l.head != NULL) {
		printf("| %-5d ", ++stt);
        printf("| %-12lld ", l.head->student.ID);
        printf("| %-25s ", l.head->student.name);
        printf("| %-2d/%-2d/%-7d ", l.head->student.date_of_birth.day, l.head->student.date_of_birth.month, l.head->student.date_of_birth.year);
		printf("| %-20s ", l.head->student.from);
		printf("| %-15s ", l.head->student.Class);
		printf("| %-5.2f |", l.head->student.GPA);
        printf("\n---------------------------------------------------------------------------------------------------------------------\n");
        l.head = l.head->next;
    }
}
