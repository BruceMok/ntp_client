/**
 * @file    main.cpp
 * <pre>
 * Copyright (c) 2018, Gaaagaa All rights reserved.
 * 
 * �ļ����ƣ�main.cpp
 * �������ڣ�2018��11��15��
 * �ļ���ʶ��
 * �ļ�ժҪ��ʹ��NTPЭ���ȡ����ʱ����Ĳ��Գ���
 * 
 * ��ǰ�汾��1.0.0.0
 * ��    �ߣ�
 * ������ڣ�2018��11��15��
 * �汾ժҪ��
 * 
 * ȡ���汾��
 * ԭ����  ��
 * ������ڣ�
 * �汾ժҪ��
 * </pre>
 */

#include "VxNtpHelper.h"

#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif // _WIN32

#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

/**
* @class vxWSASocketInit
* @brief �Զ� ����/ж�� WinSock ��Ĳ����ࡣ
*/
class vxWSASocketInit
{
    // constructor/destructor
public:
    vxWSASocketInit(x_int32_t xit_main_ver = 2, x_int32_t xit_sub_ver = 0)
    {
        WSAStartup(MAKEWORD(xit_main_ver, xit_sub_ver), &m_wsaData);
    }

    ~vxWSASocketInit(x_void_t)
    {
        WSACleanup();
    }

    // class data
protected:
    WSAData      m_wsaData;
};

#endif // _WIN32

/**********************************************************/
/**
 * @brief ���ʱ�����Ϣ��
 */
x_void_t ts_output(x_cstring_t xszt_name, const x_ntp_time_context_t * const xtm_ctxt)
{
    printf("\t%s : %04d-%02d-%02d_%02d-%02d-%02d.%03d\n",
        xszt_name,
        xtm_ctxt->xut_year,
        xtm_ctxt->xut_month,
        xtm_ctxt->xut_day,
        xtm_ctxt->xut_hour,
        xtm_ctxt->xut_minute,
        xtm_ctxt->xut_second,
        xtm_ctxt->xut_msec);
}

//====================================================================

int main(int argc, char * argv[])
{
    x_int32_t xit_err = -1;

    x_ntp_time_context_t xnpt_timec;
    x_uint64_t xut_timev = 0ULL;

#ifdef _WIN32
    vxWSASocketInit gInit;
#endif // _WIN32

    //======================================
    // ���õ� NTP ��������ַ�б�

    std::vector< std::string > xvec_ntp_host;
    xvec_ntp_host.push_back(std::string("1.cn.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("2.cn.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("3.cn.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("0.cn.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("cn.pool.ntp.org"           ));
    xvec_ntp_host.push_back(std::string("tw.pool.ntp.org"           ));
    xvec_ntp_host.push_back(std::string("0.tw.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("1.tw.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("2.tw.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("3.tw.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("pool.ntp.org"              ));
    xvec_ntp_host.push_back(std::string("time.windows.com"          ));
    xvec_ntp_host.push_back(std::string("time.nist.gov"             ));
    xvec_ntp_host.push_back(std::string("time-nw.nist.gov"          ));
    xvec_ntp_host.push_back(std::string("asia.pool.ntp.org"         ));
    xvec_ntp_host.push_back(std::string("europe.pool.ntp.org"       ));
    xvec_ntp_host.push_back(std::string("oceania.pool.ntp.org"      ));
    xvec_ntp_host.push_back(std::string("north-america.pool.ntp.org"));
    xvec_ntp_host.push_back(std::string("south-america.pool.ntp.org"));
    xvec_ntp_host.push_back(std::string("africa.pool.ntp.org"       ));
    xvec_ntp_host.push_back(std::string("ca.pool.ntp.org"           ));
    xvec_ntp_host.push_back(std::string("uk.pool.ntp.org"           ));
    xvec_ntp_host.push_back(std::string("us.pool.ntp.org"           ));
    xvec_ntp_host.push_back(std::string("au.pool.ntp.org"           ));

    //======================================

    for (std::vector< std::string >::iterator itvec = xvec_ntp_host.begin(); itvec != xvec_ntp_host.end(); ++itvec)
    {
        xut_timev = 0ULL;
        xit_err = ntp_get_time(itvec->c_str(), NTP_PORT, 5000, &xut_timev);
        if (0 == xit_err)
        {
            ntp_tmctxt_bv(xut_timev, &xnpt_timec);   // ת���� ��-��-��_ʱ-��-��.���� ��ʱ����Ϣ
            ts_output(itvec->c_str(), &xnpt_timec);  // ���ʱ����Ϣ
        }
        else
        {
            // ����ʧ�ܣ���������ΪӦ��ʱ......
        }
    }

    //======================================

    return xit_err;
}
