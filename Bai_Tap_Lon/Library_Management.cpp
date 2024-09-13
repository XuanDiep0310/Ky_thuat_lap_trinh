#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book { 
    char ID[6];                    /* Mã số sách */
    char name_book[25];            /* Tên sách */
    char author[25];               /* Tác giả */
    int publishing_year;           /* Năm xuất bản */
    char category[20];             /* Thể loại sách */
};

void Export(Book *book, int size);                        /* Hàm xuất danh sách sách ra màn hình */
void import(Book *book, int size);                        /* Hàm nhập thông tin 1 cuốn sách */
void add_book(Book *book, int *size);         			  /* Hàm thêm thông tin 1 cuốn sách vào vị trí bất kì */
void erase_book(Book *book, int *size);					  /* Hàm xóa 1 quyển sách theo ID */
void search_by_ID(Book *book, int size);       		      /* Hàm tra cứu thông tin 1 cuốn sách theo ID */
void sort_by_ID(Book *book, int size);         			  /* Hàm sắp xếp sách theo ID */
void changed(Book *book, int size);            			  /* Hàm thay đổi thông tin 1 cuốn sách theo ID */
void write_to_file(Book *book, int size);     			  /* Hàm ghi thông tin sách vào file */
void read_from_file(Book *book, int *size);   			  /* Hàm đọc thông tin sách từ file */
bool check_duplicate_ID(Book *book, int size, char ID[]); /* Hàm kiểm tra mã số sách có bị trùng không */

int main() {
	int size = 0;
    Book *ptr;
	ptr = (Book *) malloc(10*sizeof(Book));
    
	printf("\n===================== M E N U =======================");
	printf("\n|  0. Xuat danh sach sach ra man hinh               |");
	printf("\n|  1. Them 1 cuon sach                              |");
	printf("\n|  2. Xoa 1 cuon sach theo ID                       |");
	printf("\n|  3. Thay doi thong tin sach theo ID               |");
	printf("\n|  4. Tra cuu thong tin sach theo ID                |");
	printf("\n|  5. Sap xep sach theo ID                          |");
	printf("\n|  6. Dem so luong sach trong danh sach             |");
	printf("\n|  7. Ghi thong tin sach vao file                   |");
	printf("\n|  8. Doc du lieu tu file                           |");
	printf("\n|  9. Xoa man hinh                                  |");
	printf("\n| 10. Thoat chuong trinh                            |");
	printf("\n=====================================================");

	while(true) {
		int choose;
		printf("\nVui long nhap lua chon: ");
        do {
            scanf("%d", &choose); getchar();
            if(choose < 0 || choose > 10)
                printf("Lua chon khong hop le, vui long nhap lai: ");
        } while(choose < 0 || choose > 10);
		switch(choose) {
            case 0:
                Export(ptr, size);
                break;
			case 1: 
				add_book(ptr, &size);
				break;
			case 2: 
				erase_book(ptr, &size);
				break;
			case 3:
				changed(ptr, size);
				break;
			case 4:
				search_by_ID(ptr, size);
				break;
			case 5:
				sort_by_ID(ptr, size);
				break;
			case 6:
				printf("Co %d cuon sach trong danh sach !", size);
				break;
			case 7:
				write_to_file(ptr, size);
				break;
			case 8:
				read_from_file(ptr, &size);
				break;
			case 9:
				system("cls");
				break;
			case 10: 
                printf("Cam on da su dung chuong trinh, hen gap lai <3 !");
				return 0;
		}
	}
	free(ptr);
}

/* Hàm xuất danh sách sách ra màn hình */
void Export(Book *book, int size) {
    if(size == 0) {
        printf("Danh sach trong !");
        return;
    }
	printf("=================================================================================================================\n");
	printf("| %-4s | %-10s | %-25s | %-25s | %-10s | %-20s |", "STT", "Ma So Sach", "Ten Sach", "Tac Gia", "Nam XB", "The Loai");
	printf("\n=================================================================================================================\n");
	for (int i = 0; i < size; i++) {
		printf("| %-4d ", i+1);
		printf("| %-10s ", (book+i)->ID); 
		printf("| %-25s ", (book+i)->name_book); 
		printf("| %-25s ", (book+i)->author); 
        printf("| %-10d ", (book+i)->publishing_year);
        printf("| %-20s |", (book+i)->category);
		printf("\n-----------------------------------------------------------------------------------------------------------------\n");
	}
}

/* Hàm kiểm tra mã số sách có bị trùng không */
bool check_duplicate_ID(Book *book, int size, char ID[]) {
	for(int i = 0; i < size; i++) {
		if(strcmp((book+i)->ID, ID) == 0) return true;
	}
	return false;
}

/* Hàm nhập thông tin 1 cuốn sách */
void import(Book *book, int size) {
    printf("Nhap ma sach: ");
	char ID[6];
	do {	
		fgets(ID, sizeof(ID), stdin);
    	ID[strcspn(ID, "\n")] = '\0';
		if(check_duplicate_ID(book, size, ID))
			printf("Ma so %s da ton tai, vui long nhap lai: ", ID);
	} while(check_duplicate_ID(book, size, ID));
	strcpy(book->ID, ID);
    
    printf("Nhap ten sach: ");
    fgets(book->name_book, sizeof(book->name_book), stdin);
    book->name_book[strcspn(book->name_book, "\n")] = '\0';
    printf("Nhap tac gia: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = '\0';
    printf("Nhap nam XB: ");
    do {
        scanf("%d", &book->publishing_year); getchar();
        if(book->publishing_year < 0)
            printf("Nam XB khong hop le, vui long nhap lai: ");
    } while(book->publishing_year < 0);
    printf("Nhap the loai sach: ");
    fgets(book->category, sizeof(book->category), stdin);
    book->category[strcspn(book->category, "\n")] = '\0';
}

/* Hàm thêm thông tin 1 cuốn sách vào vị trí bất kì */
void add_book(Book *book, int *size) {
	int index;
	printf("Nhap vi tri can them sach: "); 
    do {
	    scanf("%d", &index); getchar();
	    if (index < 1 || index > *size + 1)
		    printf("Vi tri nhap vao khong hop le, vui long nhap lai: ");
	} while(index < 1 || index > *size + 1);

	// Cấp phát thêm một ô nhớ cho danh sách sách
	book = (Book *)realloc(book, (*size + 1) * sizeof(Book));
	if (book == NULL) {
		printf("Loi khi cap phat bo nho!\n");
		return;
	}

	// Dịch chuyển các sách sau vị trí cần thêm để tạo chỗ trống cho sách mới
	for(int i = *size-1; i >= index-1; i--) {
			*(book+i+1) = *(book+i);
	}

	// Nhập thông tin cho sách mới
	import(book+index-1, *size);
	*size += 1; //Tăng số lượng sách sau khi thêm
	printf("Them sach thanh cong !");
}

/* Hàm xóa 1 quyển sách theo ID */
void erase_book(Book *book, int *size) {
	char ID[6];
	printf("Nhap ma so cua sach can xoa: ");
	fgets(ID, sizeof(ID), stdin);
	ID[strcspn(ID, "\n")] = '\0';
	
	int ok = -1;
	for(int i = 0; i < *size; i++) {
		if(strcmp((book+i)->ID, ID) == 0) {
			ok = i;
			break;
		}
	}
	if(ok == -1) {
		printf("Khong ton tai sach co ma so %s !", ID);
		return;
	}
	// Di chuyển các phần tử phía sau lên trước để ghi đè phần tử cần xoá
	for (int i = ok; i < *size - 1; i++) {
    	*(book + i) = *(book + i + 1);
	}

	// Giảm kích thước danh sách đi 1
	(*size)--;

	printf("Sach co ma so %s da duoc xoa !", ID);
}

/* Hàm tra cứu thông tin 1 cuốn sách theo ID */
void search_by_ID(Book *book, int size) {
	char ID[6];
	printf("Nhap ma so cua sach can tra cuu: ");
	fgets(ID, sizeof(ID), stdin);
	ID[strcspn(ID, "\n")] = '\0';
	
	int ok = -1;
	for(int i = 0; i < size; i++) {
		if(strcmp((book+i)->ID, ID) == 0) {
			ok = i;
			break;
		}
	}
	if(ok == -1) {
		printf("Khong ton tai sach co ma so %s !", ID);
		return;
	}
	printf("Thong tin cuon sach co ma %s la\n", ID);
	printf("Ten sach: %s\n", (book+ok)->name_book);
	printf("Tac gia: %s\n", (book+ok)->author);
	printf("Nam XB: %d\n", (book+ok)->publishing_year);
	printf("The loai: %s", (book+ok)->category);
}

/* Hàm sắp xếp sách theo ID */
void sort_by_ID(Book *book, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			if (strcmp((book+i)->ID, (book+j)->ID) > 0) {
				Book temp = *(book+i);
				*(book+i) = *(book+j);
				*(book+j) = temp;
			}
		}
	}
	printf("Sap xep thanh cong !");
}

/* Hàm thay đổi thông tin 1 cuốn sách theo ID */
void changed(Book *book, int size) {
	char ID[6];
	printf("Nhap ma so cua sach can thay doi thong tin: ");
	fgets(ID, sizeof(ID), stdin);
	ID[strcspn(ID, "\n")] = '\0';
	
	int ok = -1;
	for(int i = 0; i < size; i++) {
		if(strcmp((book+i)->ID, ID) == 0) {
			ok = i;
			break;
		}
	}
	if(ok == -1) {
		printf("Khong ton tai sach co ma so %s !", ID);
		return;
	}
	import(book+ok, size);
	printf("Thay doi thong tin cuon sach co ma so %s thanh cong !", ID);
}

/* Hàm ghi thông tin sách vào file */
void write_to_file(Book *book, int size) {
	FILE *fp;
	if((fp = fopen("books.txt", "w")) == NULL) {
		printf("Loi khi mo file books.txt !");
		return;
	}

	for(int i = 0; i < size; i++) {
		fprintf(fp, "%s|", (book+i)->ID);
		fprintf(fp, "%s|", (book+i)->name_book);
		fprintf(fp, "%s|", (book+i)->author);
		fprintf(fp, "%d|", (book+i)->publishing_year);
		fprintf(fp, "%s", (book+i)->category);
		fprintf(fp, "\n");
	}

	fclose(fp);
	printf("Ghi du lieu vao file thanh cong !");
}

/* Hàm đọc thông tin sách từ file */
void read_from_file(Book *book, int *size) {
	FILE *fp;
    char line[256]; // Đọc mỗi dòng tối đa có 256 ký tự
    if ((fp = fopen("books.txt", "r")) == NULL) {
        printf("Loi khi mo file books.txt !");
        return;
    }
	*size = 0;
    while (fgets(line, sizeof(line), fp)) {
		// Bỏ ký tự '\n' nếu có
        line[strcspn(line, "\n")] = '\0';

        char *token;
        // Lưu trữ ID
        token = strtok(line, "|");
        strcpy((book+*size)->ID, token);

        // Lưu trữ tên
        token = strtok(NULL, "|");
        strcpy((book+*size)->name_book, token);

        // Lưu trữ tác giả
        token = strtok(NULL, "|");
        strcpy((book+*size)->author, token);
		
		// Lưu trữ năm XB
        token = strtok(NULL, "|");
        sscanf(token, "%d", &(book+*size)->publishing_year);

        // Lưu trữ thể loại sách
        token = strtok(NULL, "|");
        strcpy((book+*size)->category, token);

		(*size)++;
    }
    fclose(fp);
    printf("Doc du lieu tu file thanh cong !");
}
