#include <stdio.h>
#include "cJSON.h"

char * makeJson()
{
    cJSON * pJsonRoot = NULL;

    pJsonRoot = cJSON_CreateObject();
    if(NULL == pJsonRoot)
    {
        //error happend here
        return NULL;
    }
    cJSON_AddStringToObject(pJsonRoot, "name", "hello world");
    cJSON_AddNumberToObject(pJsonRoot, "age", 10010);
    cJSON_AddBoolToObject(pJsonRoot, "bool", 1);
    /*cJSON * pSubJson = NULL;
    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddStringToObject(pSubJson, "subjsonobj", "a sub json string");
    cJSON_AddItemToObject(pJsonRoot, "subobj", pSubJson);*/

    char * p = cJSON_Print(pJsonRoot);
  // else use :
    // char * p = cJSON_PrintUnformatted(pJsonRoot);
    if(NULL == p)
    {
        //convert json list to string faild, exit
        //because sub json pSubJson han been add to pJsonRoot, so just delete pJsonRoot, if you also delete pSubJson, it will coredump, and error is : double free
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    //free(p);

    cJSON_Delete(pJsonRoot);

    return p;
}

void parseJson(char * pMsg)
{
    if(NULL == pMsg)
    {
        return;
    }
    cJSON * pJson = cJSON_Parse(pMsg);
    if(NULL == pJson)
    {
        // parse faild, return
      return ;
    }

    // get string from json
    cJSON * pSub = cJSON_GetObjectItem(pJson, "name");
    if(NULL == pSub)
    {
        //get object named "hello" faild
    }
    printf("obj_1 name: %s\n", pSub->valuestring);

    // get number from json
    pSub = cJSON_GetObjectItem(pJson, "age");
    if(NULL == pSub)
    {
        //get number from json faild
    }
    printf("obj_1 age: %d\n", pSub->valueint);

    // get bool from json
    pSub = cJSON_GetObjectItem(pJson, "bool");
    if(NULL == pSub)
    {
        // get bool from json faild
    }
    printf("obj_1 bool: %d\n", pSub->valueint);

 // get sub object
  /*  pSub = cJSON_GetObjectItem(pJson, "subobj");
    if(NULL == pSub)
    {
        // get sub object faild
    }
    cJSON * pSubSub = cJSON_GetObjectItem(pSub, "subjsonobj");
    if(NULL == pSubSub)
    {
        // get object from subject object faild
    }
    printf("sub_obj_1 : %s\n", pSubSub->valuestring);*/

    cJSON_Delete(pJson);
}

int main1()
{
    char * p = makeJson();
    if(NULL == p)
    {
        return 0;
    }
    printf("%s\n", p);
    parseJson(p);
    free(p); //千万不要忘记释放内存呀，cJSON_Print()函数或者cJSON_PrintUnformatted（）产生的内存，使用free(char *)进行释放
    return 0;
}
int main2()
{
    FILE * fp = fopen("./obj.txt","r+");
    char file[1024]={0};
    char buf[128];
    char *temp = file;
    while(fgets(buf,128,fp))
    {
        int i;
        for(i=0; i < strlen(buf);i++)
        {
            *(temp++) = buf[i];
        }
        memset(buf,128,0);

    }
    printf("%s",(char *)file);
    cJSON * pJson = cJSON_Parse((char *)file);
    cJSON *psub = cJSON_GetObjectItem(pJson,"name");
    printf("name is : %s\n",psub->valuestring);
    fclose(fp);
    return 0;
}
int main()
{
    FILE * fp = fopen("./people.txt","r+");
    char file[1024]={0};
    char buf[128];
    char *temp = file;
    while(fgets(buf,128,fp))
    {
        if(buf[0] == '/' && buf[1] == '/')//让cjson解析的时候支持注释
            continue;
        int i;
        for(i=0; i < strlen(buf);i++)
        {
            *(temp++) = buf[i];
        }
        memset(buf,128,0);

    }
    printf("%s",(char *)file);
    cJSON * pJson = cJSON_Parse((char *)file);
    cJSON *psub = cJSON_GetObjectItem(pJson,"people");
    cJSON *psub2;
    cJSON *psub3;
    cJSON *psub4;
    int i;
    for(i = 0; i < cJSON_GetArraySize(psub); i++){
        psub2 = cJSON_GetArrayItem(psub,i);
        psub3 = cJSON_GetObjectItem(psub2,"firstName");
        psub4 = cJSON_GetObjectItem(psub2,"lastName");
        printf("firstName is : %s,lastName:%s \n",psub3->valuestring,psub4->valuestring);

    }
    cJSON_Delete(pJson);//把根节点干掉就OK了

    fclose(fp);
    return 0;
}
