#include<stdio.h>
#include<string.h>

typedef unsigned char  INT8U;                   /* Unsigned  8 bit quantity                           */
typedef unsigned short INT16U;                  /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                  /* Unsigned 32 bit quantity                           */



INT8U HexToChar(INT8U sbyte)
{
    sbyte &= 0x0F;
    if (sbyte < 0x0A) return (sbyte + '0');
    else return (sbyte - 0x0A + 'A');
}

INT8U CharToHex(INT8U schar)
{
    if (schar >= '0' && schar <= '9') return (schar - '0');
    else if (schar >= 'A' && schar <= 'F') return (schar - 'A' + 0x0A);
    else if (schar >= 'a' && schar <= 'f') return (schar - 'a' + 0x0A);
    else return 0;
}

INT16U HexToAscii(INT8U *dptr, INT8U *sptr, INT16U len)
{
    INT16U i;
    INT8U  stemp;
    
    for (i = 1; i <= len; i++) {
        stemp = *sptr++;
        *dptr++ = HexToChar(stemp >> 4);
        *dptr++ = HexToChar(stemp & 0x0F);
    }
    return (2 * len);
}

INT16U AsciiToHex(INT8U *dptr, INT8U *sptr, INT16U len)
{
    INT16U i;
    INT8U  dtemp, stemp;
    
    if (len % 2) return 0;
    len /= 2;
    for (i = 1; i <= len; i++) {
        stemp   = CharToHex(*sptr++);
        dtemp   = stemp << 4;
        *dptr++ = CharToHex(*sptr++) | dtemp;
    }
    return len;
}

/*******************************************************************
**  函数名  :  DecToAscii
**  函数描述:  将一个值转换为10进制表达的ASCII码,如0x1122(十进制值为4386),则转换ASCII后为"4386"
**  参数:      [out] dptr:   转换后ASCII码缓存指针
**             [in]  data:   待转换的数值
**             [in]  reflen: 转换后位数,如果为0表示实际位数;如果不为0,则不满位数在前面填'0'
**  返回参数:  成功返回转换后的长度(包含结束符)，失败返回0
********************************************************************/
INT8U DecToAscii(INT8U *dptr, INT32U data, INT8U reflen)
{
    INT8U i, len, temp;
    INT8U *tempptr;
    
    len     = 0;
    tempptr = dptr;
    for (;;) {
        *dptr++ = HexToChar(data % 10);
        len++;
        if (data < 10) break;
        else data /= 10;
    }
    if (len != 0) {
        dptr = tempptr;
        for (i = 0; i < (len/2); i++) {
            temp = *(dptr + i);
            *(dptr + i) = *(dptr + (len - 1 - i));
            *(dptr + (len - 1 - i)) = temp;
        }
        if (reflen > len) {
            dptr = tempptr + (len - 1);
            for (i = 1; i <= reflen; i++) {
                if (i <= len) *(dptr + (reflen - len)) = *dptr;
                else *(dptr + (reflen - len)) = '0';
                dptr--;
            }
            len = reflen;
        }
    }
    return len;
}

/*******************************************************************
**  函数名  :  AsciiToDec
**  函数描述:  将一串ASCII码按照10进制表达方式转换为HEX值,如ASCII为"4386",转换后为0x1122(十进制值为4386)
**  参数:      [in] sptr:   待转换ASCII码
**             [in] slen:   待转换ASCII码长度
**  返回参数:  返回转换后hex值
********************************************************************/
INT32U AsciiToDec(INT8U *sptr, INT8U slen)
{
    INT32U result;
    
    result = 0;
    for (; slen > 0; slen--) {
        result = result * 10 + CharToHex(*sptr++);
    }
    return result;
}

















