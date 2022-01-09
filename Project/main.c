#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct node
{
    int priority;
    int ucakID;
    int saat;
    int inis_saati;
    int kalkis_saati;
    struct node *next;
} NODE;
NODE *front = NULL;

// enqueue method
void enqueue(int ucakID,int priority,int saat)
{
    NODE *temp,*gezgin;

    temp = (NODE *)malloc(sizeof(NODE));
    temp->ucakID = ucakID;
    temp->priority = priority;
    temp->saat = saat;
    //  temp->inis_saati=priority;
    //  temp->kalkis_saati=priority+1;
    if( front == NULL || priority < front->priority ) // kuyruk bos ise veya eklenen eleman ilk elemandan daha oncelikli ise
    {
        temp->next = front; // onceki ilk eleman artýk tempten sonraya atildi
        front = temp; // ilk elemaný yeni eklenen eleman yaptik
    }
    else
    {
        gezgin = front;// gezgin eleman basa atildi ve gezdirilecek
        while( gezgin->next != NULL && gezgin->next->priority <= priority ) // gezgin son siraya gelmedigi surece ve gezenin sonrasinin onceligi suanki oncelikten az oldugu sure
            gezgin=gezgin->next; // gezgin bir sonraki elemana atliyor dongu sartýný bozdugu yere yani yerlesecegi yere kadar geliyor
        temp->next = gezgin->next; // temp in sonrasi gezginin sonrasi olarak atandi
        gezgin->next = temp; // gezginin sonraki elemani  da bizim yeni eklenen elemanimiz oldu ve kuyruga eklenmis oldu
    }

}
void oncelik_kontrol()
{
    FILE *fp = fopen("output.txt","w+");
    NODE *ptr;
    ptr = front;
    int i=0;
    int sayac=256;
    int sira[sayac][6];
    if(front == NULL)
        printf("KUYRUK bos\n");

    else
    {

        while(ptr != NULL)
        {
            sira[i][0]=ptr->saat;
            sira[i][1]=ptr->ucakID;
            sira[i][2]=ptr->priority;
            sira[i][3]=ptr->priority;
            sira[i][4]=0;
            sira[i][5]=ptr->priority+1;
            i++;
            ptr = ptr->next;
        }
    }
    sayac=i;
    ptr = front;
    i=0;
    int j=0,k=0;
    int  tut=0;
    int tmp[1];


    while(ptr != NULL)
    {

        k=0;
        tut=0;

        if(sira[i][3]==sira[i+1][3])
        {
            while(sira[i+tut][3]==sira[i+tut+1][3])
            {
                tut++;


            }
            for(j=1; j<=tut; j++)
            {
                sira[i+j][3]++;
                sira[i+j][4]++;
                sira[i+j][5]++;
                if(sira[i+j][4]>3)
                {
                    sira[i+j][4]=sira[i+j][4]%4;
                    if(sira[i+j][4]>=3)
                    {
                        sira[i+j+1][5]=sira[i+j][5];
                    }



                }
            }
        }
        i++;
        ptr=ptr->next;

    }


    printf("ONCELIK_ID  |    UCAK_ID   |    TALEP SAATI    |   INIS SAATI  |   GECIKME SURESI  |   KALKIS SAATI   | \n");
    fprintf(fp,"ONCELIK_ID  |    UCAK_ID   |    TALEP SAATI    |   INIS SAATI  |   GECIKME SURESI  |   KALKIS SAATI   | \n");

    for(i=0; i<sayac; i++)
    {
        if(sira[i][4]<3 &&  sira[i][3]<25 )
        {
            fprintf(fp,"\n\t%d\t\t%d\t\t %d\t\t %d \t\t%d \t\t%d\n",sira[i][0],sira[i][1],sira[i][2],sira[i][3],sira[i][4],sira[i][5]%25);// dosyaya yazdiriyoruz
            printf("\t%d\t\t%d\t\t %d\t\t %d \t\t%d \t\t%d\n",sira[i][0],sira[i][1],sira[i][2],sira[i][3],sira[i][4],sira[i][5]%25);// dosyaya yazdiriyoruz

        }

    }


    printf("\nOutput Dosyasi Olusturuldu\n");
    fclose(fp);
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");

}



void dequeue()
{
    NODE *temp;
    // kuyrukta islem yapacak hic ucak kalmadi
    if(front == NULL)
        printf("KUYRUK bos\n");
    else
    {
        temp = front;
        printf("Islemi tamamlanan Ucak No : %d\n", temp->ucakID);
        printf("Ucagin inis talep ettigi saat : %d\n",(temp->saat));
        front = front->next; // ilk siradaki ucak ciktigi icin sira basi artik ilktekinden sonraki eleman oldu
        free(temp); // islemi tamamlanan ucak memory den temizlendi
    }
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");
}
void yazdir()
{

    FILE *fp = fopen("output.txt","r+");
    NODE *ptr;
    ptr = front;
    int i=0;
    int sayac=256;
    int sira[sayac][6];
    if(front == NULL)
        printf("KUYRUK bos\n");

    else
    {

        while(ptr != NULL)
        {
            sira[i][0]=ptr->saat;
            sira[i][1]=ptr->ucakID;
            sira[i][2]=ptr->priority;
            sira[i][3]=ptr->priority;
            sira[i][4]=0;
            sira[i][5]=ptr->priority+1;
            i++;
            ptr = ptr->next;
        }
    }
    sayac=i;
    ptr = front;
    i=0;
    int j=0,k=0;
    int  tut=0;
    int tmp[1];


    while(ptr != NULL)
    {

        k=0;
        tut=0;

        if(sira[i][3]==sira[i+1][3])
        {
            while(sira[i+tut][3]==sira[i+tut+1][3])
            {
                tut++;


            }
            for(j=1; j<=tut; j++)
            {
                sira[i+j][3]++;
                sira[i+j][4]++;
                sira[i+j][5]++;
                if(sira[i+j][4]>3)
                {
                    sira[i+j][4]=sira[i+j][4]%4;
                    if(sira[i+j][4]>=3)
                    {
                        sira[i+j+1][5]=sira[i+j][5];
                    }
                }
            }

        }

        i++;
        ptr=ptr->next;

    }


    int dizi[20];
    j=0;
    for(i=0; i<sayac; i++)
    {
        if(sira[i][4]<3 &&  sira[i][3]<25 )
        {

            printf("%d Id li %d oncelikli ucak %d saatinde inip %d saatinde kalkmistir\n",sira[i][1],sira[i][0],sira[i][3],sira[i][5]%25);

        }
        else
        {
            dizi[j]=i;
            j++;
        }


    }
    printf("\n\n");
    for(i=0; i<j; i++)
    {
        if(sira[dizi[i]][4]==3)
        {
            printf("%d Id li 3 kere ertelenmeden oturu iptal edilip Sabiha Gokcene Gonderilmistir...\n",sira[dizi[i]][1]);

        }

    }

    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");

}
void inis()
{
    NODE *ptr;
    ptr = front;
    int i=0;
    int sayac=256;
    int sira[sayac][6];
    if(front == NULL)
        printf("KUYRUK bos\n");

    else
    {

        while(ptr != NULL)
        {
            sira[i][0]=ptr->saat;
            sira[i][1]=ptr->ucakID;
            sira[i][2]=ptr->priority;
            sira[i][3]=ptr->priority;
            sira[i][4]=0;
            sira[i][5]=ptr->priority+1;
            i++;
            ptr = ptr->next;
        }
    }
    sayac=i;
    ptr = front;
    i=0;
    int j=0,k=0;
    int  tut=0;
    int tmp[1];


    while(ptr != NULL)
    {

        k=0;
        tut=0;

        if(sira[i][3]==sira[i+1][3])
        {
            while(sira[i+tut][3]==sira[i+tut+1][3])
            {
                tut++;


            }
            for(j=1; j<=tut; j++)
            {
                sira[i+j][3]++;
                sira[i+j][4]++;
                sira[i+j][5]++;
                if(sira[i+j][4]>3)
                {
                    sira[i+j][4]=sira[i+j][4]%4;
                    if(sira[i+j][4]>=3)
                    {
                        sira[i+j+1][5]=sira[i+j][5];
                    }
                }
            }

        }

        i++;
        ptr=ptr->next;

    }
    printf("ONCELIK_ID  |    UCAK_ID   |    I-SAAT    \n");
    for(i=0; i<sayac; i++)
    {
        if(sira[i][4]<3 &&  sira[i][3]<25 )
        {

            printf("\t%d\t%d\t\t%d\n",sira[i][0],sira[i][1],sira[i][3]);

        }

    }
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");

}
void kalkis()
{

    NODE *ptr;
    ptr = front;
    int i=0;
    int sayac=256;
    int sira[sayac][6];
    if(front == NULL)
        printf("KUYRUK bos\n");

    else
    {

        while(ptr != NULL)
        {
            sira[i][0]=ptr->saat;
            sira[i][1]=ptr->ucakID;
            sira[i][2]=ptr->priority;
            sira[i][3]=ptr->priority;
            sira[i][4]=0;
            sira[i][5]=ptr->priority+1;
            i++;
            ptr = ptr->next;
        }
    }
    sayac=i;
    ptr = front;
    i=0;
    int j=0,k=0;
    int  tut=0;
    int tmp[1];


    while(ptr != NULL)
    {

        k=0;
        tut=0;

        if(sira[i][3]==sira[i+1][3])
        {
            while(sira[i+tut][3]==sira[i+tut+1][3])
            {
                tut++;


            }
            for(j=1; j<=tut; j++)
            {
                sira[i+j][3]++;
                sira[i+j][4]++;
                sira[i+j][5]++;
                if(sira[i+j][4]>3)
                {
                    sira[i+j][4]=sira[i+j][4]%4;
                    if(sira[i+j][4]>=3)
                    {
                        sira[i+j+1][5]=sira[i+j][5];
                    }
                }
            }

        }

        i++;
        ptr=ptr->next;

    }
    printf("ONCELIK_ID  |    UCAK_ID   |    K-SAAT    \n");
    for(i=0; i<sayac; i++)
    {
        if(sira[i][4]<3 &&  sira[i][3]<25 )
        {

            printf("\t%d\t%d\t\t%d\n",sira[i][0],sira[i][1],sira[i][5]%25);

        }

    }
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");

}

void oncelik_rapor()
{
    NODE *ptr;
    NODE *temp;
    ptr = front;
    if(front == NULL)
        printf("KUYRUK bos\n");
    else
    {
        while(ptr != NULL)
        {
            if(ptr->priority == ptr->next->priority && ptr->saat > ptr->next->saat)
            {
                printf("%d id li ucak ayni saatte %d id li ucaktan daha oncelikli oldugu icin one alinir \n",ptr->next->ucakID,ptr->ucakID);
                temp = ptr->next;
                ptr->next = ptr;
                ptr = temp;
            }
            ptr = ptr->next;
        }
        printf("\n-----------\n");

    }
}

void output()
{
    FILE *fp = fopen("output.txt","w");
    NODE *ptr;
    ptr = front;
    if(front == NULL)
        printf("KUYRUK bos\n");
    else
    {

        printf("ONCELIK_ID  |    UCAK_ID   |    I-SAAT    |    K-SAAT\n");
        fprintf(fp,"ONCELIK_ID  |    UCAK_ID   |    I-SAAT    |    K-SAAT\n");
        while(ptr != NULL)
        {
            fprintf(fp,"%5d       |   %5d      |    %5d     |    %5d      \n",ptr->saat,ptr->ucakID,ptr->priority,(ptr->priority)+1);
            printf("%5d       |   %5d      |    %5d     |    %5d      \n",ptr->saat,ptr->ucakID,ptr->priority,(ptr->priority)+1);

            ptr = ptr->next;
        }

    }
    printf("\nOutput Dosyasi Olusturuldu\n");
    fclose(fp);
    puts("\nDevam etmek icin bir tusa basin ...");
    getch();
    system("cls");
}

int main()
{
    FILE *dosya = fopen("input.txt", "r");
    int secim, ucakID, priority,saat;
    int MAX = 255;
    char satir[MAX];
    printf("\n\n\t\tHAVALIMANI UCUS YONETIM SISTEMINE HOSGELDINIZ\n\n\n");
    do
    {

        printf("1 - Dosyadan Ekle\n");
        printf("2 - Kuyruktan Cikar\n");
        printf("3 - Yazdir\n");
        printf("4 - Output Dosyasini Yazdir\n");
        printf("5 - Inis Siralamasi\n");
        printf("6 - Kalkis Siralamasi\n");
        printf("7 - Oncelik degisim durum raporu\n");
        printf("8 - Quit\n");
        printf("Yapmak istediginiz islem : ");
        scanf("%d", &secim);
        int i;
        int dizi[28][3];
        switch(secim)
        {
        case 1:
            system("cls");

            i=0;
            printf("\n%-20s%-20s%-20s%\n", "ONCELIK ID", "UCAK ID", "TALEP SAATI");
            while(fgets(satir, MAX, dosya))
            {


                if(i!=0)
                {
                    char * bol;
                    bol = strtok (satir," ");
                    int bolIndex = 0;
                    while (bol != NULL)
                    {
                        bolIndex++;
                        if(bolIndex > 0 && bolIndex<=3)
                        {
                            int deger = atoi(bol);
                            printf("\t%-8d",deger);
                            if(bolIndex==1)
                            {
                                priority = deger;
                            }
                            else if(bolIndex==2)
                            {
                                ucakID = deger;
                            }
                            else if(bolIndex==3)
                            {
                                saat = deger;
                            }
                        }

                        bol = strtok(NULL, " ");
                    }
                    printf("\n");
                    enqueue(ucakID,saat,priority);

                }
                i=1;

            }
            puts("\nDevam etmek icin bir tusa basin ...");
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            dequeue();
            break;
        case 3:
            system("cls");
            yazdir();
            break;

        case 4:
            system("cls");
            printf("\nOutput Dosyasi olusturuluyor...\n");
            oncelik_kontrol();
            break;
        case 5:
            system("cls");
            inis();
            break;
        case 6:
            system("cls");
            kalkis();
            break;
        case 7:
            oncelik_rapor();
            break;
        case 8:
            break;
        default :
            printf("Yanlis secim\n");
        }
    }
    while(secim!=7);


    fclose(dosya);
    return 0;
}
