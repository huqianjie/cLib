/**
  ******************************************************************************
  * @file    configfile.c
  * @author  Dragon.Chen
  * @version V1.0.0
  * @date    12-02-2013
  * @brief
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 上海今中网络科技有限公司 </center></h2>
  ******************************************************************************
  */

#include "configfile.h"

CONFIG_FILE_INFO cfi;

/**
  * @brief  生成默认配置文件信息
  * @param  NULL
  * @retval 成功返回0，否则-1
  */
static int generate_default_configfile()
{
    FILE *fp = NULL;
    /************ 默认配置文件 */
    const char *default_configfile = \
        "AppDaemon	 = 1\n" \
        "ThreadCount  = 4\n" \
        "ServerPort   = 63000\n" \
        "WindowVer    = V1.0000\n" \
        "WindowFVer   = V0.0000\n" \
        "AndroidVer   = V1.0000\n" \
        "AndroidFVer  = V0.0000\n" \
        "PidPath	     = /sonicom/conf/openvpn/conf/vpnserver.pid\n" \
        "RootCertPath = /sonicom/conf/openvpn/keys/ca.crt\n" \
        "SerCertPath  = /sonicom/conf/openvpn/keys/server.crt\n" \
        "SerKeyPath   = /sonicom/conf/openvpn/keys/server.key\n" \
        "DBName		 = /sonicom/conf/openvpn/conf/vpnserver.db\n";

    /************ 路径不存在，则创建 */
    if (mkdir( VPN_CNF_PTPT, 0755) < 0)
    {
        if (errno != EEXIST)
        {
            MSG(LOG_ERROR, "[generate_default_configfile] Fail to create directory!");
            return -1;
        }
    }

    /************ 将默认配置文件写入文件 */
    if ((fp=fopen(VPN_CNF_PATH, "wt")) == NULL)
    {
        MSG(LOG_ERROR, "[generate_default_configfile] Fail to open the default configfile!");
        return -1;
    }
    if (EOF == fputs(default_configfile, fp))
    {
        MSG(LOG_ERROR, "[generate_default_configfile] Fail to generate the default configfile!");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    return 0;
}


/**
  * @brief  读取配置文件信息
  * @param  NULL
  * @retval 成功返回0，否则-1
  */
int get_config_file_info()
{
    int  cnt = 0;
    char **m_list = NULL;
    char buffer[PARSE_STRING_LEN];

    ZeroMemory(&cfi, sizeof(cfi));
    ZeroMemory(buffer, PARSE_STRING_LEN);

    /************ 读取配置文件 */
    if (read_content_from_configfile(VPN_CNF_PATH, &m_list, &cnt) == FALSE)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to find the configfile!");

        /************ 生成默认的配置文件 */
        if (generate_default_configfile() == -1)
            return -1;
        else
        {
            MSG(LOG_WARNING, "[init_config_file] Create the default config file Successfully, the application will be exited.");
            exit(EXIT_FAILURE);
        }
    }

    /************ 程序是否后台化 */
    if ( strcmp(getAttributtionItem("AppDaemon", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the AppDaemon!");
        return -1;
    }
    else
    {
        cfi.app_daemon = atoi(buffer) != 1 ? 0 : 1;
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ 获取线程数 */
    if ( strcmp(getAttributtionItem("ThreadCount", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the ThreadCount!");
        return -1;
    }
    else
    {
        cfi.thread_count = atoi(buffer) <= 0 ? 1 : (atoi(buffer) > VPN_MAX_NUM_OF_THREAD ?
                            VPN_MAX_NUM_OF_THREAD : atoi(buffer) );
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ 获取服务器端口 */
    if ( strcmp(getAttributtionItem("ServerPort", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the ServerPort!");
        return -1;
    }
    else
    {
        cfi.server_port = atoi(buffer);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ window客户端最新版本 */
    if ( strcmp(getAttributtionItem("WindowVer", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the WindowVer!");
        return -1;
    }
    else
    {
        cfi.window_version = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.window_version, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ window客户端强制更新最低版本 */
    if ( strcmp(getAttributtionItem("WindowFVer", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the WindowFVer!");
        return -1;
    }
    else
    {
        cfi.window_f_version = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.window_f_version, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ android客户端最新版本 */
    if ( strcmp(getAttributtionItem("AndroidVer", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the AndroidVer!");
        return -1;
    }
    else
    {
        cfi.android_version = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.android_version, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ android客户端强制更新最低版本 */
    if ( strcmp(getAttributtionItem("AndroidFVer", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the androidFVer!");
        return -1;
    }
    else
    {
        cfi.android_f_version = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.android_f_version, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

     /************ pid路径 */
    if ( strcmp(getAttributtionItem("PidPath", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the PidPath!");
        return -1;
    }
    else
    {
        cfi.pid_path = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.pid_path, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ RootCertPath路径 */
    if ( strcmp(getAttributtionItem("RootCertPath", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the RootCertPath!");
        return -1;
    }
    else
    {
        cfi.rootcert = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.rootcert, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ server.crt 路径 */
    if ( strcmp(getAttributtionItem("SerCertPath", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the SerCertPath!");
        return -1;
    }
    else
    {
        cfi.servercert = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.servercert, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ server.key 路径 */
    if ( strcmp(getAttributtionItem("SerKeyPath", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the SerKeyPath!");
        return -1;
    }
    else
    {
        cfi.serverkey = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.serverkey, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************ 数据库路径 */
    if ( strcmp(getAttributtionItem("DBName", buffer, PARSE_STRING_LEN, "", m_list, cnt), "") == 0)
    {
        MSG(LOG_ERROR, "[init_config_file] Fail to get the DBName!");
        return -1;
    }
    else
    {
        cfi.db_name = (char*)calloc(strlen(buffer), 1);
        strncpy(cfi.db_name, buffer, strlen(buffer)-1);
        ZeroMemory(buffer, PARSE_STRING_LEN);
    }

    /************* 释放内存 */
    free_configfile_memory(m_list, &cnt);

    LOG("%s\nAppDaemon = %d\n"
        "ThreadCount = %d\n"
        "ServerPort = %d\n"
        "WindowVer = %s\n"
        "WindowFVer = %s\n"
        "AndroidVer = %s\n"
        "AndroidFVer = %s\n"
        "PidPath = %s\n"
        "RootCertPath = %s\n"
        "SerCertPath  = %s\n"
        "SerKeyPath = %s\n"
        "DBName = %s\n%s\n\n",

        "-----------------config file info-----------------",
        cfi.app_daemon,
        cfi.thread_count,
        cfi.server_port,
        cfi.window_version,
        cfi.window_f_version,
        cfi.android_version,
        cfi.android_f_version,
        cfi.pid_path,
        cfi.rootcert,
        cfi.servercert,
        cfi.serverkey,
        cfi.db_name,
        "--------------end of config file info-------------");

    return 0;
}



/******************* (C) COPYRIGHT 2013 上海今中网络科技有限公司 *****END OF FILE****/
