//
//  main.c
//  Heal
//
//  Created by Burak Dusun on 09/08/16.
//  Copyright © 2016 Burak Dusun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define SATIR_BOYUTU 10000
#define DUZELTME_ORANI 3
#define THRESHOLD 5
#define ARTI_EKSI 10
//#define DOSYA_ACMA_HATA 5



int main(int argc, const char * argv[]) {
    
    int eskiSayac=0;
    int tahminSayisi;
    int i,j,sayac;
    
    FILE *fRead;
    FILE *fWrite;
    
    char dosyaAdiRead[100];
    char dosyaAdiWrite[100];
    char tmpSatir[SATIR_BOYUTU];
    
    int *gercekDegerler;
    int *tahminiDegerler;
    int *duzeltilenDegerler;
    
    
    printf("Tahmin dosyasinin adini giriniz: ");
    scanf("%s",dosyaAdiRead);
    
    //printf("Düzeltilmiş dosyasinin adini giriniz: ");
    //scanf("%s",dosyaAdiWrite);
    
    fRead = fopen(dosyaAdiRead,"r");
    
    //fWrite = fopen(dosyaAdiWrite, "w");
    
    sayac = 0;
    
    
    while(sayac<3){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        if(tmpSatir[0] == '='){
            sayac++;
        }
    }
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //printf("%s",tmpSatir);
    
    tahminSayisi = 0;
    
    while (tmpSatir[0] != '\n'){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        tahminSayisi++;
    }
    tahminSayisi--;
    printf("Tahmin Sayisi = %d\n",tahminSayisi);
    
    fclose(fRead);
    
    gercekDegerler = (int *) calloc(tahminSayisi, sizeof(int));
    tahminiDegerler = (int *) calloc(tahminSayisi, sizeof(int));
    duzeltilenDegerler = (int *) calloc(tahminSayisi, sizeof(int));
    
    fRead = fopen(dosyaAdiRead, "r");
    
    sayac = 0;
    while(sayac<3){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        if(tmpSatir[0] == '='){
            sayac++;
        }
    }
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //printf("%s",tmpSatir);
    
    sayac=0;
    i=0;
    j=0;
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    char tmpSayi[3];
    int k=0;
    while (tmpSatir[0] != '\n'){
        while(tmpSatir[j] != ','){
            j++;
        }
        j++;
        k=0;
        while(tmpSatir[j] != ':'){
            tmpSayi[k] = tmpSatir[j];
            k++;
            j++;
        }
        tmpSayi[k] = '\0';
        gercekDegerler[i] = atoi(tmpSayi);
        
        while(tmpSatir[j] != ','){
            j++;
        }
        j++;
        k=0;
        while(tmpSatir[j] != ':'){
            tmpSayi[k] = tmpSatir[j];
            k++;
            j++;
        }
        tmpSayi[k] = '\0';
        tahminiDegerler[i] = atoi(tmpSayi);
        duzeltilenDegerler[i] = tahminiDegerler[i];
        if(gercekDegerler[i] != tahminiDegerler[i]){
            eskiSayac++;
        }
        i++;
        j=0;
        k=0;
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
    }
    
    //for(i=0;i<tahminSayisi;i++){
    //    printf("i=%d, gercekDeger = %d, tahmin = %d\n",i,gercekDegerler[i],tahminiDegerler[i]);
    //}
    
    int bas,son;
    int aralik = 1;
    int duzeltmeAraligi;
    int max1, max2;
    int maxKordinat1 = 0;
    int maxKordinat2;
    int max1Frekans = -5;
    int max2Frekans;
    int maxKontrol;
    int tmpFrekans;
    int max2Kontrol;
    int baslangic=0;
    
    sayac = 0;
    i = 1;
    while(i<tahminSayisi-aralik)
    {
        baslangic = i-1;
        max1 = tahminiDegerler[i-1];
        max2 = tahminiDegerler[i-1];
        max1Frekans = 1;
        max2Frekans = 1;
        tmpFrekans = 1;
        maxKordinat1 = i-1;
        maxKordinat2 = i-1;
        for(j = 1; j < aralik; j++)
        {
            if(tahminiDegerler[i]==tahminiDegerler[i-1]){
                tmpFrekans++;
            }
            
            else
            {
                if(tmpFrekans>=max1Frekans)
                {
                    max1Frekans = tmpFrekans;
                    maxKordinat1 = i;
                    max1 = tahminiDegerler[i-1];
                }
                else
                {
                    if(tmpFrekans>=max2Frekans && tahminiDegerler[i-1] != max1)
                    {
                        max2Frekans = tmpFrekans;
                        maxKordinat2 = i;
                        max2 = tahminiDegerler[i-1];
                    }
                }
                tmpFrekans = 1;
            }
            i++;
        }
        
        
        
        if((maxKordinat2 + ARTI_EKSI) >=  i)
        {
            j = maxKordinat2+1;
            max2Kontrol = 0;
            while((j < tahminSayisi) && (j < (j+2*ARTI_EKSI)) )
            {
                if(max2 == tahminiDegerler[j])
                {
                    max2Kontrol++;
                }
                j++;
            }
            if(max2Kontrol > THRESHOLD)
            {
                j = maxKordinat2-max2Frekans;
                max2Kontrol = THRESHOLD;
                while((max2Kontrol >= THRESHOLD ))
                {
                    max2Kontrol = 0;
                    for(k = j; k > j-ARTI_EKSI; k--)
                    {
                        if(tahminiDegerler[k]==max2)
                        {
                            max2Kontrol++;
                        }
                    }
                    j -= ARTI_EKSI;
                }
                j += ARTI_EKSI;
                for(k = j; k < i; k++)
                {
                    duzeltilenDegerler[k] = max2;
                }
                for(k = baslangic; k < j; k++)
                {
                    duzeltilenDegerler[k] = max1;
                }
            }
        }
        else
        {
            if((maxKordinat2 - max2Frekans - ARTI_EKSI) <=  baslangic)
            {
                j = (maxKordinat2 - max2Frekans - ARTI_EKSI);
                
                if(j < 0)
                {
                    j = 0;
                }
                
                max2Kontrol = 0;
                while(j <= (maxKordinat2-max2Frekans))
                {
                    if(max2 == tahminiDegerler[j])
                    {
                        max2Kontrol++;
                    }
                    j++;
                }
                
                
                if(max2Kontrol > THRESHOLD)
                {
                    j = maxKordinat2;
                    max2Kontrol = THRESHOLD;
                    while((max2Kontrol >= THRESHOLD ))
                    {
                        max2Kontrol = 0;
                        for(k = j; k < j+ARTI_EKSI; k++)
                        {
                            if(tahminiDegerler[k]==max2)
                            {
                                max2Kontrol++;
                            }
                        }
                        j += ARTI_EKSI;
                    }
                    j -= ARTI_EKSI;
                    for(k = baslangic; k < j; k++)
                    {
                        duzeltilenDegerler[k] = max2;
                    }
                    for(k = j; k < i; k++)
                    {
                        duzeltilenDegerler[k] = max1;
                    }
                }
            }
            else
            {
                for(k = baslangic; k < i; k++)
                {
                    duzeltilenDegerler[k] = max1;
                }
            }
        }
        i++;
    }
    
    for(i=0; i<tahminSayisi; i++){
        printf("i=%d, gercek deger=%d, tahmini deger=%d, duzeltilen deger=%d ",i,gercekDegerler[i],tahminiDegerler[i],duzeltilenDegerler[i]);
        if(gercekDegerler[i]!=duzeltilenDegerler[i]) {
            printf("+ ");
            sayac++;
            
        }
        if(duzeltilenDegerler[i] != tahminiDegerler[i]){
            printf("* ");
        }
        printf("\n");
    }
    float basari = ( (float)(tahminSayisi-sayac) / tahminSayisi)*100;
    float eskiBasari = ((float)(tahminSayisi-eskiSayac) / tahminSayisi)*100;
    printf("hataSayisi=%d, eskiBasariOrani=%f, yeniBasariOrani=%f\n",sayac,eskiBasari, basari);
    
    
    
    
    fclose(fRead);
    //fclose(fWrite);
    
    return 0;
}
