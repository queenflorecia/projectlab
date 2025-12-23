int cariCatatan(struct Catatan c[],int n, int key){
    for (i = 0; i < n; i++) {
        if (c[i].kodeTanggal == key) {
            return i;
        }
    }
    return -1;
}

void header(){
	printf("%-3s %-20s %-20s %-20s %-10s\n","No.","Kategori","Luar Masuk","Tanggal","Nominal");
	printf("==================================================================================\n");
}
	
void printCatatan(struct Catatan c, int index){
	
	printf("%-3d ", index+1);
	printf("%-20s ", tipeApa(c.tipe));
	printf("%-20s ", masukLuar(c.masukLuar));
	printf("%-2d ", c.hari);
	printf("%-9s ", bulanApa(c.bulan));
	printf("%-9d ", c.tahun);
	printNominal(c.nominal);
	   
}

void printSeluruhCatatan(struct Catatan c[], int size, int opsi){
	int filter;
	int hmin,bmin,tmin,hmax,bmax,tmax, tglMin, tglMax;
	int noMin, noMax;
	
	if (cariCatatan(c,size,0)==0) {
		printf("Belum Ada Catatan\n");
		return;
	}	
	
	switch (opsi){
		case 1:
			header();
			i=0;
			while (c[i].kodeTanggal>0) {
				printCatatan(c[i],i);
				i++;
			}
			break;
		case 2: 
			printf("0) Pemasukan, 1) Kos/Sewa, 2) Transportasi,\n");
			printf("3) Makanan, 4) Tagihan Bulanan, 5) Perlengkapan Kuliah,\n");
			printf("6) Keperluan Pribadi, 7) Hiburan, 8) Lainnya.\n");
			ask();
			scanf("%d",&filter);
			
			puts("");
			header();
			i=0;
			while (c[i].kodeTanggal>0) {
				if (c[i].tipe==filter) printCatatan(c[i],i);
				i++;
			}
			
			break;
		case 3:
			printf("Dari tanggal (hh bb tttt): ");
			scanf("%d %d %d",&hmin,&bmin,&tmin);
			tglMin = kodeTgl(hmin,bmin,tmin);
			
			printf("Sampai tanggal (hh bb tttt): ");
			scanf("%d %d %d",&hmax,&bmax,&tmax);
			tglMax = kodeTgl(hmax,bmax,tmax);
			
			puts("");
			header();
			i=0;
			while (c[i].kodeTanggal>0) {
				if (c[i].kodeTanggal>=tglMin&&c[i].kodeTanggal<=tglMax) printCatatan(c[i],i);
				i++;
			}
			
			break;
		case 4: 
			printf("Nominal minimal: ");
			scanf("%d",&noMin);
			
			printf("Nominal maximal: ");
			scanf("%d",&noMax);
			
			puts("");
			header();
			for (i=0;i<size;i++) if (c[i].nominal>=noMin&&c[i].nominal<=noMax) printCatatan(c[i],i);
			
			break;
		case 5:	break;
		
		case 6: {
    		long long saldo = 0;
    		i = 0;
    		while (c[i].kodeTanggal > 0) {
        		if (c[i].masukLuar == 1)
            		saldo += c[i].nominal;
        		else if (c[i].masukLuar == 2)
            		saldo -= c[i].nominal;
        		i++;
    		}
			puts("==== SALDO SAAT INI ====");
    		printNominal(saldo);
    		break;
		}

	}
}

void cekCatatan(struct Catatan c[],int size){
	puts("CEK CATATAN");
	
	int opsi;
	
	if (cariCatatan(c,size,0)==0) {
		printf("Belum Ada Catatan\n");
		return;
	}	
	
	sortTanggal(c,size);
	
	do{
		puts("");
		printf("1. Lihat seluruh transaksi\n");
		printf("2. Filter sesuai kategori\n");
		printf("3. Filter sesuai tanggal\n");
		printf("4. Filter sesuai nominal\n");
		printf("5. Kembali ke menu\n");
		printf("6. Cek saldo\n");
		do{
			ask();
			scanf("%d",&opsi);
		} while (opsi<1||opsi>6);
		puts("");
		printSeluruhCatatan(c,size,opsi);
	} while (opsi!=5);
		

}
