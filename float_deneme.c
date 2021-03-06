#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#define oklidBoyutu 3
#define LINESIZE 10000

void dosyaErr(FILE *);
void floatMErr(float **);
void floatDErr(float *);


int atlamaMik;
int kontrolAdet;


int isCSV(char *dosyaAdi)
{
    int i = strlen(dosyaAdi);
    i--;
    if ((dosyaAdi[i]=='v')&&(dosyaAdi[--i]=='s')&&(dosyaAdi[--i]=='c')&&(dosyaAdi[--i]=='.'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void labelBul(char *dosyaAdi, char *label, int labelType)
{
    int i=0,j=0;
    if(labelType == 1)
    {
        while(dosyaAdi[i] != '_')
        {
            label[i] = dosyaAdi[i];
            i++;
        }
        label[i] = '\0';

    }
    else if (labelType == 0)
    {
        while(dosyaAdi[i] != '_')
        {
            i++;
        }
        i++;
        while(dosyaAdi[i] != '_')
        {
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = dosyaAdi[i]; // _'da kalmamasi icin
        i++;
        j++;
        while(dosyaAdi[i] != '_')
        {
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = '\0';
    }

}

float ortalamaAritmetikBul(float *degerler)
{
    int i;
    float toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += degerler[i];
    }
    if(toplam == HUGE_VAL){
    printf("\n---------------------------------\n");
        for(i=0; i<kontrolAdet; i++)
        {
        printf("%f,",degerler[i]);
        }
        exit(0);
    }
    return toplam/kontrolAdet;

}


float ortalamaHarmonikBul(float *degerler)
{
    int i;
    float toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += 1/degerler[i];
    }
    return kontrolAdet/toplam;

}

float ortalamaKuadratikBul(float *degerler)
{
    int i;
    float toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += (degerler[i]*degerler[i]);
    }
    return sqrt(toplam/kontrolAdet);

}

float standartSapma(float varyans)
{
    return sqrt(varyans);
}



float varyansBul(float *degerler,float ortalama)
{
    int i;
    float toplam = 0;

    for(i=0; i<kontrolAdet; i++)
    {
        toplam += pow((degerler[i]-ortalama),2);
    }

//    if(toplam == HUGE_VAL){
//        printf("\n%f,%f",degerler[i],ortalama);
//    }

    return toplam/kontrolAdet;

}


void anlikOrtalamalar(float *degerler,int baslangic, float *anlikAritmetikOrt,float *anlikHarmonikOrt,float *anlikKuadratikOrt)
{
    int i;
    float fark;
    float aritmatikToplam , harmonikToplam , kuadratikToplam ;
    aritmatikToplam = harmonikToplam = kuadratikToplam = 0;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;

    for(i=1; i<kontrolAdet; i++)
    {

        fark = degerler[baslangic]-degerler[j];
        aritmatikToplam += fark;
        harmonikToplam += 1/fark;
        kuadratikToplam += fark*fark;

        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;

    }

    *anlikAritmetikOrt = aritmatikToplam/kontrolAdet;
    *anlikHarmonikOrt = kontrolAdet/harmonikToplam;
    *anlikKuadratikOrt = sqrt(kuadratikToplam/kontrolAdet);

}


float varyasyonKatSayisi(float stdSapma,float ortalama,float min,float max)
{
    if (ortalama == 0)
    {
        if(stdSapma>0)
        {
            return max;
        }
        else if (stdSapma<0)
        {
            return min;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return stdSapma/ortalama;
    }
}


float minBul(float *degerler)
{

    int i;
    float min;
    min = degerler[0];

    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]<min)
        {
            min = degerler[i];
        }

    }
    return min;

}

float maxBul(float *degerler)
{
    int i;
    float max;
    max = degerler[0];

    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]>max)
        {
            max = degerler[i];
        }

    }
    return max;
}



float ranjBul(float min, float max)
{
    return max - min;
}

float minIncBul(float *degerler,int baslangic)  //minimum artis
{

    int i;

    float min = 100000.0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;

    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark>0) && (fark<min))
        {
            min = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;

    }

    if(min == 100000.0){
        min = 0;
    }

    return min;
}

float maxIncBul(float *degerler,int baslangic)  //maximum artis
{

    int i;

    float max = 0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;

    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark>0) && (fark>max))
        {
            max = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;

    }

    return max;
}




float minRedBul(float *degerler,int baslangic)  //minimum azalis
{
    int i;

    float min = -100000.0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;

    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark<0) && (fark>min))
        {
            min = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;

    }
    if(min == -100000.0){
        min = 0;
    }

    return min;
}



float maxRedBul(float *degerler,int baslangic)  //maximum artis
{
    int i;

    float max = 0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;

    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark<0) && (fark<max))
        {
            max = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;

    }

    return max;

}



int partition(float dizi[],int l, int r)
{
    float pivot = dizi[l];
    int i = l;
    int j = r+1;
    float tmp;

    do
    {
        do
        {
            i++;
        }
        while(i<j && dizi[i]<=pivot);

        do
        {
            j--;
        }
        while(dizi[j]>pivot);

        tmp = dizi[i];
        dizi[i]=dizi[j];
        dizi[j]=tmp;
    }
    while(i<j);

    tmp = dizi[i];
    dizi[i]=dizi[j];
    dizi[j]=tmp;

    tmp = dizi[l];
    dizi[l]=dizi[j];
    dizi[j]=tmp;

    return j;
}
void quickS(float dizi[],int l, int r)
{
    int pivotAddr;
    if(l<r)
    {
        pivotAddr = partition(dizi,l,r);
        quickS(dizi,l,pivotAddr-1);
        quickS(dizi,pivotAddr+1,r);
    }
}

void modMedianBul (float *degerler,float *median, float *mod)
{

    int i,j=0;
    float *tmp;
    float maxMod=1.0;
    float tmpMod=1.0;
    int maxModI=0;
    int bolum,kalan,indis;
    tmp = (float *) malloc(kontrolAdet*sizeof(float));

    for(i=0; i<kontrolAdet; i++)
    {
        tmp[i]=degerler[i];
    }
    //quickSort(tmp,0,kontrolAdet);
    quickS(tmp,0,kontrolAdet-1);
    /**
     buradaki islemlerin amaci cift sayida veri oldugu taktirde ortadaki iki sayiyi bulup ortalamasini almak. if kullanmak pahali geldi.
     */
    bolum = kontrolAdet/2;
    kalan = kontrolAdet%2;
    indis = bolum + kalan - 1;
    *median = (tmp[bolum] + tmp[indis])/2;
    //cift sayıda olma durumunda kontrol edip ortalamasını almak lazım

    j=1;
    while (j<kontrolAdet)
    {
        while(j<kontrolAdet && tmp[j]==tmp[j-1])
        {
            j++;
            tmpMod++;
        }
        if(tmpMod>maxMod)
        {
            maxModI=j-1;
            maxMod=tmpMod;
        }
        j++;
        tmpMod=1;
    }

    *mod = tmp[maxModI];
    free(tmp);
}




void islem(float **degerler,int baslangic, int argSayisi, char ayrac, FILE **fWrite)
{

    int x;
    float min;
    float max;
    float ranj;
    float minInc;
    float maxInc;
    float minRed;
    float maxRed;
    float median;
    float mod;
    float aritmetikOrtalama;
    float harmonikOrtalama;
    float kuadratikOrtalama;
    float stdSapma;
    float varyans;
    float anlikAritmetikOrt;
    float anlikHarmonikOrt;
    float anlikKuadratikOrt;
    float varyasyonKatSayi;

    for(x=0; x<argSayisi; x++)
    {
        min = minBul(degerler[x]);
        max = maxBul(degerler[x]);
        ranj = ranjBul(min,max);
        minInc = minIncBul(degerler[x],baslangic);
        maxInc = maxIncBul(degerler[x],baslangic);
        minRed = minRedBul(degerler[x],baslangic);
        maxRed = maxRedBul(degerler[x],baslangic);

        aritmetikOrtalama = ortalamaAritmetikBul(degerler[x]);
        harmonikOrtalama = ortalamaHarmonikBul(degerler[x]);
        kuadratikOrtalama = ortalamaKuadratikBul(degerler[x]);
        varyans = varyansBul(degerler[x],aritmetikOrtalama);
        stdSapma = standartSapma(varyans);
        anlikOrtalamalar(degerler[x],baslangic,&anlikAritmetikOrt,&anlikHarmonikOrt,&anlikKuadratikOrt);
        varyasyonKatSayi = varyasyonKatSayisi(stdSapma,aritmetikOrtalama,min,max);
        modMedianBul(degerler[x],&median,&mod);
        //printf("\nMin: %lf, Max: %lf,",geometrikOrtalama,varyans);

        fprintf(*fWrite,"%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c%f%c",minRed,ayrac,maxRed,ayrac,minInc,ayrac,maxInc,ayrac,min,ayrac,max,ayrac,ranj,ayrac,aritmetikOrtalama,ayrac,harmonikOrtalama,ayrac,kuadratikOrtalama,ayrac,mod,ayrac,median,ayrac,stdSapma,ayrac,varyans,ayrac,anlikAritmetikOrt,ayrac,anlikHarmonikOrt,ayrac,anlikKuadratikOrt,ayrac,varyasyonKatSayi,ayrac);
    }

}

int main()
{



    int i,j,k,x,y;
    int indis;
    float oklidDegeri;

    int r ;
    int argSayisi = 0;
    char dosyaAdiOkuma[100];
    char dosyaAdiYazma[] = "features.arff";
    char tmpSatir[LINESIZE];
    char ayrac;
    int kelimeUzunlugu;

    float **degerler;
    float **oklids;

    int degerSayisi;
    float tmpDeger = 0.0;
    float dDonustur = 1.0;
    float isaret = 1.0;


    int sure;
    int frekans;
    int atlamaOrani;
    int labelType = 0;

    char *ozellikler[] = {"MINRED","MAXRED","MININC","MAXINC","MINVAL","MAXVAL", "RANGE",
                          "ARTMEAN","HARMEAN", "QUADMEAN", "MOD", "MEDIAN", "STD","VAR", "IEARTMEAN", "IEHARMEAN",
                          "IEQUADMEAN", "COV"
                         };

    // char *labels[] = {"walking","car","bus","tram","metro1","metro2","marmaray","metrobus","bicycle","ferry","n"};
    char *labels[] = {"walking_walking","minibus_sitting","minibus_standing","car_car","bus_sitting","tram_sitting","metroH_sitting","metroK_sitting","marmaray_sitting","metrobus_sitting","ferry_sitting","bus_standing","tram_standing","metroH_standing","metroK_standing","marmaray_standing","metrobus_standing","ferry_standing"};

    char *labels1[]= {"walking","minibus","car","bus","tram","metro","metrobus","ferry"};

    char label[100];
    char alan[100];
    int kacinciKelime;
    int yazildi=0;
    int ozellikSayisi = 18;
    int labelSayisi = 18;
    int labelSayisi1= 8;

    FILE *fRead;
    FILE *fWrite;

    //fRead = fopen(dosyaAdiOkuma,"r");
    //dosyaErr(fRead);

    //printf("\nDosya Adi: ");
    //scanf("%s",dosyaAdiYazma);

    printf("\nAzaltilmis labellar?(1 - evet, 0 - hayir) ");
    scanf("%d",&labelType);

    fWrite = fopen(dosyaAdiYazma,"w");
    dosyaErr(fWrite);

    fprintf(fWrite,"@RELATION vehicle_classification\n\n");


    //  fputs(tmpSatir,fWrite);

    DIR *dp;
    struct dirent *ep;

    dp = opendir ("./");
    if (dp == NULL)
    {
        exit(1);
    }
    while ((ep = readdir (dp)))
    {
        // printf("\n%d,",ep);
        strcpy(dosyaAdiOkuma,ep->d_name);
        if (isCSV(dosyaAdiOkuma))
        {
            labelBul(dosyaAdiOkuma,label,labelType);
            fRead = fopen(dosyaAdiOkuma,"r");
            //printf("Dosya isleniyor: %s ...\n",dosyaAdiOkuma);
            fgets(tmpSatir,LINESIZE,fRead);

            i = 0;

            if(!yazildi)
            {


                while(tmpSatir[i])
                {

                    if(tmpSatir[i] == ',' || tmpSatir[i] == ';')
                    {

                        argSayisi++;
                        //printf("argSayisi= %d\n",argSayisi);
                        ayrac = tmpSatir[i];
                    }
                    i++;
                }
                i = 1;
                j= 0;
                /**
                 Bir azaltma sebebim sondaki iki kolonun ölçülecek bir yanı olmaması.
                 */
                argSayisi--;
                i=0;
                kacinciKelime=0;
                k=0;
                kelimeUzunlugu=0;
                while(kacinciKelime<argSayisi)
                {
                    if(tmpSatir[i] != ayrac)
                    {
                        alan[kelimeUzunlugu] = tmpSatir[i];
                        printf("%c",alan[kelimeUzunlugu]);
                        kelimeUzunlugu++;
                    }
                    else
                    {
                        alan[kelimeUzunlugu] = '\0';
                        printf("\n");
                        for(k=0; k<ozellikSayisi; k++)
                        {
                            fprintf(fWrite,"@ATTRIBUTE \"%s_%s\" NUMERIC\n",alan,ozellikler[k]);
                        }
                        kelimeUzunlugu=0;
                        kacinciKelime++;
                    }
                    i++;
                }

                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"ACC_%s\" NUMERIC\n",ozellikler[k]);
                }

                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"GYRO_%s\" NUMERIC\n",ozellikler[k]);
                }
                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"MAG_%s\" NUMERIC\n",ozellikler[k]);
                }

                fprintf(fWrite,"@ATTRIBUTE label {");
                labelSayisi--;
                if(labelType == 0)
                {
                    for(i=0; i<labelSayisi-1; i++)
                    {
                        fprintf(fWrite,"%s,",labels[i]);
                    }
                    fprintf(fWrite,"%s",labels[i]);
                }
                else if (labelType == 1)
                {
                    for(i=0; i<labelSayisi1; i++)
                    {
                        fprintf(fWrite,"%s,",labels1[i]);
                    }
                }

                fprintf(fWrite,"}\n\n@DATA\n");


                printf("Arg Sayisi= %d\n",argSayisi);


                printf("\nFrekans Nedir? (hz) ");
                scanf("%d",&frekans);

                printf("\nNe Kadarlik Zaman Araliginin Ozelligini Cikarmak İstersiniz? (milisaniye cinsinden) ");
                scanf("%d",&sure);

                printf("\nAtlama oranini yuzde olarak giriniz(Tam Sayi) ");
                scanf("%d",&atlamaOrani);


                kontrolAdet = (sure*frekans)/1000;
                atlamaMik = (kontrolAdet*atlamaOrani)/100;
                //   ozellikSayisi = (degerSayisi-kontrolAdet)/atlamaMik + 1;
                oklids = (float**) malloc(oklidBoyutu*sizeof(float*));
                floatMErr(oklids);
                for(i=0; i<oklidBoyutu; i++)
                {
                    oklids[i] = (float*) malloc(kontrolAdet * sizeof(float));
                    floatDErr(oklids[i]);
                }

                degerler = (float**) malloc(argSayisi * sizeof(float*));
                floatMErr(degerler);
                for(i=0; i<argSayisi; i++)
                {
                    degerler[i] = (float*) malloc(kontrolAdet * sizeof(float));
                    floatDErr(degerler[i]);
                }

                yazildi=1;
            }

            degerSayisi = 0;
            r = 0;


            while(fgets(tmpSatir,LINESIZE,fRead))
            {

                if(degerSayisi >= kontrolAdet)
                {
                    degerSayisi = kontrolAdet - atlamaMik;

                    for(x=0; x<oklidBoyutu; x++)
                    {
                        indis = x*3;

                        for(y=0; y<kontrolAdet; y++)
                        {
                            oklidDegeri = degerler[indis][y]*degerler[indis][y] + degerler[indis+1][y]*degerler[indis+1][y] + degerler[indis+2][y]*degerler[indis+2][y];
                            oklids[x][y] = sqrt(oklidDegeri);
                        }
                    }


                    islem(degerler,r,argSayisi,ayrac,&fWrite);
                    islem(oklids,r,oklidBoyutu,ayrac,&fWrite);

                    fprintf(fWrite,"%s",label);
                    putc('\n',fWrite);


                }

                j=0;
                for(i=0; i<argSayisi; i++)
                {
                    isaret = 1.0;
                    tmpDeger = 0.0;
                    dDonustur = 1.0;
                    if(tmpSatir[j]== '-')
                    {
                        isaret = -1.0;
                        j++;
                    }

                    while(tmpSatir[j] != ayrac && tmpSatir[j] != '.')
                    {

                        tmpDeger *= 10;
                        tmpDeger += (tmpSatir[j] - '0');
                        j++;
                    }
                    if(tmpSatir[j] != ayrac)
                        j++;
                    while(tmpSatir[j] != ayrac)
                    {
                        dDonustur *= 10;
                        tmpDeger = tmpDeger + (tmpSatir[j] - '0')/dDonustur;
                        j++;
                    }
                   // printf("%f,",tmpDeger*isaret);
                    degerler[i][r] = tmpDeger*isaret;

                    j++;

                }
               // printf("\n");
                r++;
                r %= kontrolAdet;
                degerSayisi++;
            }
            //printf("\n\n");

            fclose(fRead);
        }
    }



    for(i=0; i<argSayisi; i++)
    {
        free(degerler[i]);

    }


    free(degerler);


    fclose(fWrite);




    return 0;
}



/********************************************************/


void dosyaErr(FILE *f)
{
    if(!f)
    {
        printf("Dosya Bulunamadi");
        exit(0);
    }
}

void floatMErr(float **d)
{
    if(!d)
    {
        printf("Matris Olusturulamadi");
        exit(0);
    }
}

void floatDErr(float *d)
{
    if(!d)
    {
        printf("Alan Olusturulamadi");
        exit(0);
    }
}


/*******************************************************************/

