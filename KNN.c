// KNN 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define TEST_SIZE 60
#define REF_SIZE 90
typedef struct
{
	double pos1;
	double pos2;
	double pos3;
	double pos4;
	char classy[50];
} Info;

typedef struct
{
	double distance;
	char classInfo[50];
} Dist;

int comp(const void*a, const void*b); 
int main(int argc, char *argv[])
{
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;

	int i,j,h;
	int k = atoi(argv[4]);
	int correct1=0, correct2=0, correct3=0;
	char flower1[] = "Iris-setosa";
	char flower2[] = "Iris-versicolor";
	char flower3[] = "Iris-virginica";
	
	Info *test = (Info*)malloc(sizeof(Info)*TEST_SIZE);
	if(test == NULL)	printf("TEST 동적할당실패!");
	Info *ref = (Info*)malloc(sizeof(Info)*REF_SIZE);
	if(ref == NULL)		printf("REF 동적할당실패!");
	Dist *dist = (Dist*)malloc(sizeof(Dist)*REF_SIZE);
	if(dist == NULL)	printf("DIST 동적할당실패!");
	
	fp1 = fopen(argv[1],"r");
	if(fp1==NULL) printf("fp1 안열림");
	else printf("good \n");
	fp2 = fopen(argv[2],"r");
	if(fp2==NULL) printf("fp2 안열림");
	else printf("good \n\n");
	fp3 = fopen(argv[3],"w");
	if(fp3==NULL) printf("fp3 안열림");
	else printf("good");

	for(i=0; i<TEST_SIZE; i++)
		fscanf(fp1, "%lf,%lf,%lf,%lf,%s", &test[i].pos1, &test[i].pos2, &test[i].pos3, &test[i].pos4, test[i].classy);
	fclose(fp1);
	for(i=0; i<REF_SIZE; i++)
		fscanf(fp2, "%lf,%lf,%lf,%lf,%s", &ref[i].pos1, &ref[i].pos2, &ref[i].pos3, &ref[i].pos4, ref[i].classy);
	fclose(fp2);

	for(i=0; i<TEST_SIZE; i++)
	{
		printf("%d 번째 꽃 \n", i+1);
		double sum = 0;
		for(j=0; j<REF_SIZE; j++)// test인풋 1개로 ref 90개와 거리비교 
		{
			sum = pow(ref[j].pos1-test[i].pos1,2) + pow(ref[j].pos2-test[i].pos2,2) + pow(ref[j].pos3-test[i].pos3,2) + pow(ref[j].pos4-test[i].pos4,2); 
			dist[j].distance = sqrt(sum);
			strcpy(dist[j].classInfo,ref[j].classy);
		}
		qsort(dist,REF_SIZE,sizeof(Dist),comp);
		int cnt1=0, cnt2=0, cnt3=0;
		for(h=0; h<k; h++) //정렬된거리에서 가장가까운 k개만큼 뽑은후 클래스정보비교 
		{	
			if(!strcmp(flower1,dist[h].classInfo))	cnt1++;
			else if(!strcmp(flower2,dist[h].classInfo))	cnt2++;
			else if(!strcmp(flower3,dist[h].classInfo))	cnt3++;
			else	return -1; 
		}
			if(cnt1>=cnt2 && cnt1>=cnt3)
			{
				printf("분류결과 : %s \n", flower1 );
				if(!strcmp(flower1, test[i].classy))
					correct1++;
			}
			else if(cnt2>=cnt1 && cnt2>=cnt3)
			{
				printf("분류결과 : %s \n", flower2 );
				if(!strcmp(flower2, test[i].classy))
					correct2++;
			}
			else if(cnt3>=cnt1 && cnt3>=cnt1)
			{
				printf("분류결과 :  %s \n", flower3 );
				if(!strcmp(flower3, test[i].classy))
					correct3++;
			}
	}	
	
	printf("Iris-setosa 정확도 : %f퍼센트 \n", ((double)correct1/(TEST_SIZE/3))*100);
	printf("Iris-versicolor 정확도 : %f퍼센트 \n", ((double)correct2/(TEST_SIZE/3))*100);
	printf("Iris-virginica 정확도 : %f퍼센트 \n", ((double)correct3/(TEST_SIZE/3))*100);
	
	fclose(fp3);
	free(test);
	free(ref);
	free(dist);
	return 0;
}
int comp(const void*a, const void*b)
{
	const Dist *x = (const Dist *) a;
	const Dist *y = (const Dist *) b;
	if(x->distance < y->distance)	return -1;
	else if(x->distance > y->distance) return 1;
	return 0; 
}
