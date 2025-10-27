#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BP 128
#define SIZE 256 //128 //1024
#define MAX_ATT 10
#define MAX_ATT_NAME 30

struct buffer {
   unsigned char db; // dirty bit
   unsigned char pc; // pin count
   unsigned char nrec; // # of tuples in the page
   unsigned char nbyt; // available bytes
   char data[SIZE]; // room for data (in bytes)
};

union c_float
{
	float flt;
	char   cflt[sizeof(float)];
};

union c_double
{
	double dbl;
	char   cdbl[sizeof(float)];
};

union c_int
{
	int  num;
	char cnum[sizeof(int)];
};

struct t_buf_content { // attributes in the tuple
	char type;
	unsigned char len;
	char attname[MAX_ATT_NAME];
};

void initbuffer(struct buffer *bp)
{
	int i;
	printf("Initializing buffer ...\n");
	for (i=0;i<BP;i++)
  	{
		bp->db=0;
		bp->pc=0;
		bp->nrec=0;
		bp->nbyt=0;
		bp++;
	}
}

void copytup(struct buffer *bp,char *t, int pos)
{
	int i=pos;
	for (;i<pos+bp->nbyt;i++)
	     bp->data[i]=*(t++);
}
//
void fillbufpool(struct buffer *bp,char *t, unsigned char ttup)
{
	unsigned int i=0, found=0;
	//search for an available page in buffer
	while (!found && i < BP)
	{
    	int avail=bp[i].nrec==0?SIZE:SIZE-bp[i].nrec*ttup;
    	printf(">> (Before) Status buffer pool (Page: %d Tuples: %d Available bytes: %d)\n",i,bp[i].nrec,avail);
	    if ((bp[i].nbyt==ttup || bp[i].nbyt==0)  && ttup < avail) found=1;
        i++;
    }
    if (found)
    {
		int rpos;
		--i;
		bp[i].nrec++;
		bp[i].nbyt=ttup;
		// find the next available position to copy the tuple
		rpos=(bp[i].nrec-1)*ttup;
	    copytup(&bp[i],t,rpos);
	    int avail=bp[i].nrec==0?SIZE:SIZE-bp[i].nrec*ttup;
    	printf(">> (After) Status buffer pool (Page: %d Tuples: %d Available bytes: %d)\n",i,bp[i].nrec,avail);
		return;
    }
    // here we can implement buffer manager replacement policies
    printf("(Fatal error) No availabe room in the buffer!\n");
    return;
}

void cpystr(char *tg, char *sc, int st, int len)
{
	int i=st,j=0;
	for (;i<len+st;i++) {
	  tg[i]=sc[j++];
	}
}

void filltuple(char *tp, const void *v, unsigned char offs, struct t_buf_content bufc)
{
	char  *str=(char *)v;
	printf("Inserting data into the tuple: ");
	switch (bufc.type)
	{
	  case 'S': 
	          {
	            cpystr(tp,str,offs,bufc.len);
	            printf("%s\n",tp+offs);
	            break;
	          }
	  case 'I': 
	          {
            	int *i=(int *)v;
            	union c_int ci;
            	ci.num=*i;
	            cpystr(tp,ci.cnum,offs,bufc.len);
	            printf("%d\n",*i);
                break;
	          }
	  case 'F': 
	          {
                float *f=(float *)v;
                union c_float cf;
                cf.flt=*f;
		        cpystr(tp,cf.cflt,offs,bufc.len);
                printf("%.2f\n",*f);
                break;
	          }
	  case 'D':
	          {
	            double *d=(double *)v;
	            union c_double cd;
             	cd.dbl=*d;
	            cpystr(tp,cd.cdbl,offs,bufc.len);
	            printf("%lf\n",cd.dbl);
	            break;
	          }
	}
}

void printdebug(struct buffer *bp)
{
	int i=0;
	printf("\nBuffer Dump:\n");
	for (;i<BP;i++)
	{
	  printf("Page: %d\n",i+1);
	  if (bp[i].nrec > 0)
	  {
		printf("---%d %d\n",bp[i].nrec,bp[i].nbyt);  
      }	else printf("--- Empty\n");
    }
}

void showBuffer(struct buffer *bp, unsigned char tl, struct t_buf_content *bc, int p)
{
    int i=0, j;
    if (p<0 || p>=BP)
    { 
		printf("Invalid page number!\n");
		return;
	}
    char found0=0;
    j=0;
    int sgmt=0;
    for (;i<bp[p].nrec;i++)
    {
        for (j=0;j<MAX_ATT && bc[j].type!='@';j++)
        {
			switch (bc[j].type)
		     {
		      case 'S':
		           found0=0;
		           printf("\n%s: ",bc[j].attname);
		           for (int k=0;k<bc[j].len;k++)
		           {
					   if (bp[p].data[sgmt]==0) found0=1;
					   if (!found0)
					      printf("%c", bp[p].data[sgmt]);
					   else 
					      printf(" ");
					   sgmt++;
				   }
				   break;
		      case 'I':
		           {
		              int *v=(int *)&bp[p].data[sgmt];
                      printf("\n%s: ",bc[j].attname);
		              printf("%6d",*v);
		              sgmt+=bc[j].len;
		              break;
			       }
		      case 'F':
		           {
		              float *v=(float *)&bp[p].data[sgmt];
   		              printf("\n%s: ",bc[j].attname);
		              printf("%.2f ",*v);
		              sgmt+=bc[j].len;
		              break;
			       }
		      case 'D':
		           {
		              double *v=(double *)&bp[p].data[sgmt];
		              printf("\n%s: ",bc[j].attname);
                      printf("%.2lf ",*v);
		              sgmt+=bc[j].len;
		              break;
			       }
		    }
	    }   
  	    printf("\n");
	}
	return;
}

int main()
{
	struct buffer *bufpool;
	struct t_buf_content buf_cont[MAX_ATT];
    
	unsigned char tup_len;
	float sal;
	int   i, age, offset;
	printf("Starting buffer manager (%d pages)...\n",BP);
	bufpool=(struct buffer *)malloc(sizeof(struct buffer)*BP);
	if (bufpool==NULL)
	{
		printf("Out of memory for buffer pool!\n");
		return 0;
    }
    initbuffer(bufpool); 
    // tuples in the buffer are on the form: string 30,float ??, string 15, and int ?? 
    i=0;
    buf_cont[i].type='S'; // name
    buf_cont[i].len=30;
    strcpy(buf_cont[i].attname,"name");
    i++;
    buf_cont[i].type='F'; // salary
    buf_cont[i].len=sizeof(float);
    strcpy(buf_cont[i].attname,"salary");
    // tuple's size
    i++;
    buf_cont[i].type='S'; // gender
    buf_cont[i].len=15;
    strcpy(buf_cont[i].attname,"gender");
    //
    // tuple's size
    i++;
    buf_cont[i].type='I'; // age
    buf_cont[i].len=sizeof(int);
    strcpy(buf_cont[i].attname,"age");
    // no more tuples to store
    buf_cont[i+1].type='@'; 
    //
    tup_len=0;
    for (i=0;buf_cont[i].type!='@';i++)
        tup_len+=buf_cont[i].len;
    //
   	char *tuple=(char *)malloc(sizeof(char)*tup_len); //stores the tuple's data
    //
    // First tuple
    printf("Tuple length: %d bytes\n",tup_len);
    //        tuple    type    value        start struct
    //          |        |        |         |      |
    offset=0;
    filltuple(tuple,(void *)"João da Silva",offset,buf_cont[0]);
    ///
    sal=10.23;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=23;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len);
    ///////
    // Second tuple
    offset=0;
    filltuple(tuple,(void *)"Carlos Cavalcanti",offset,buf_cont[0]);
    ///
    sal=15.67;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=39;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    /////////////
    // Third tuple
    offset=0;
    filltuple(tuple,(void *)"Janete Constantina",offset,buf_cont[0]);
    ///
    sal=55.3;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Feminino",offset,buf_cont[2]);
    ///
    age=51;
    offset+=buf_cont[2].len;
    filltuple(tuple, (void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    //////////////////
    // Fourth tuple
    offset=0;
    filltuple(tuple,(void *)"Silvia da Silva",offset,buf_cont[0]);
    ///
    sal=33.33;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Feminino",offset,buf_cont[2]);
    ///
    age=47;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    //////////////////////
    // Fifth tupe
    offset=0;
    filltuple(tuple,(void *)"João New Page",offset,buf_cont[0]);
    ///
    sal=36.4;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=31;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    ////////////////////////////
    // Sixth 
    offset=0;
    filltuple(tuple,(void *)"Maria New Page",offset,buf_cont[0]);
    ///
    sal=51.1;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Feminino",offset,buf_cont[2]);
    ///
    age=67;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    ////////////////////////////
    // Seventh
    offset=0;
    filltuple(tuple,(void *)"Carl Seagan",offset,buf_cont[0]);
    ///
    sal=1332.2;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=83;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    //////////////////////////////
    // Eighth
    offset=0;
    filltuple(tuple,(void *)"Edgar Codd",offset,buf_cont[0]);
    ///
    sal=1000.9;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=95;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    ////////////////////////////////
    // Ninth
    offset=0;
    filltuple(tuple,(void *)"Alan Turing",offset,buf_cont[0]);
    ///
    sal=4340.4;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=156;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    ///////////////////////////////////
    // Tenth
    offset=0;
    filltuple(tuple,(void *)"Jonas Jones",offset,buf_cont[0]);
    ///
    sal=1002.12;
    offset+=buf_cont[0].len;
    filltuple(tuple, (void *)&sal,offset,buf_cont[1]);
    ///
    offset+=buf_cont[1].len;
    filltuple(tuple,(void *)"Masculino",offset,buf_cont[2]);
    ///
    age=19;
    offset+=buf_cont[2].len;
    filltuple(tuple,(void *)&age,offset,buf_cont[3]);
    ///
    printf("Insert tuple into buffer pool...\n");
    fillbufpool(bufpool,tuple,tup_len); 
    ////
    //printdebug(bufpool);
    ////
    i=0;
    while (bufpool[i].nrec>0)
    {
		printf("\nShowing page: %d",i);
		showBuffer(bufpool,tup_len,buf_cont,i);
		i++;
	}
    free(bufpool);	
    return 1;
}
