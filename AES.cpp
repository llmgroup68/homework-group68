#include<iostream>
#include"windows.h"
#include<string>
#include<ctime>
#include"time.h"
using namespace std;

const unsigned char S_box[16][16]{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

//����Կ��
unsigned char** AddRoundKey(unsigned char** sState, unsigned char Key[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <4; j++)
        {
            sState[i][j] ^= Key[i][j];
        }
    }
    return sState;
}

//���ֽڹ�S��
unsigned char SubBytes(unsigned char Aroundkey)
{
    byte h, l;
    h = Aroundkey >> 4;
    l = Aroundkey & 15;
    Aroundkey = S_box[h][l];
    return Aroundkey;
}
//����λ
unsigned char** ShiftRows(unsigned char P[4][4])
{
    uint32_t w[3];
    byte** P1 = new byte * [4];
    for (int k = 0; k < 4; k++)
    {
        P1[k] = new byte[4];
    }
    for (int i = 1; i < 4; i++)
    {
        w[i - 1] = (P[i][0] << 24) + (P[i][1] << 16) + (P[i][2] << 8) + P[i][3];//�����ֽ�ת��Ϊһ����
        int a = (i) * 8;
        w[i - 1] = w[i - 1] << a | w[i - 1] >> (32 - a);
        P1[i][0] = byte(w[i - 1] >> 24);
        P1[i][1] = byte(w[i - 1] >> 16);
        P1[i][2] = byte(w[i - 1] >> 8);
        P1[i][3] = byte(w[i - 1]);
    }
    for (int j = 0; j < 4; j++)
    {
        P1[0][j] = P[0][j];
    }
    return P1;
}
//�л��
unsigned char FiniteFieldMul(unsigned char a, unsigned char b)
{
    byte result = 0;
    byte v;
    for (int i = 0; i < 8; i++)
    {
        if ((b & 0x01) != 0)
        {
            result ^= a;
        }
        v = a >> 7;
        a <<= 1;
        if (v != 0)
        {
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return result;
}
unsigned char** MixColumns(unsigned char** b)
{
    const unsigned char a[4][4] = {
    { 0x02,0x03,0x01,0x01 },
    { 0x01,0x02,0x03,0x01 },
    { 0x01,0x01,0x02,0x03 },
    { 0x03,0x01,0x01,0x02 }
    };
    byte** result = new byte * [4];
    for (int i = 0; i < 4; i++)
    {
        result[i] = new byte[4];
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result[i][j] ^= FiniteFieldMul(a[i][k], b[k][j]);
            }
        }
    }
    return result;
}

//��Կ��չ����
const unsigned char Rcon[11] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };//�ֳ���������ֳ�������������
unsigned char* G(uint32_t w)
{
    byte* a = new byte[4];
    w = (w << 8) | (w >> 24);
    a[0] = (byte)(w >> 24);
    a[1] = (byte)(w >> 16);
    a[2] = (byte)(w >> 8);
    a[3] = (byte)(w);
    for (int i = 0; i < 3; i++)
    {
        a[i] = SubBytes(a[i]);
    }
    return a;
}
unsigned char** KeyExpansion(unsigned char key[4][4]) // keyΪ����Կ��wΪ11����չ��Կ
{
    //��0-43���������44��32�����֣�i mod 4 == 0 ʱ��w[i]=G(w[i-1])^w[i-4];��������£�w[i]=w[i-1]^w[i-4]
    //����G()���Ƚ�4�������ֽڽ��з�ת����ִ��һ�����ֽڵ�S�д���
    byte** w = new byte * [4];
    for (int i = 0; i < 4; i++)
    {
        w[i] = new byte[44];
        for (int j = 0; j < 4; j++)
        {
            w[i][j] = key[i][j];       //��һ������ԿΪ����Կ����
        }
    }
    byte* b = new byte[4];
    for (int i = 1; i < 11; i++) //4*iΪ����
    {
        for (int j = 1; j < 4; j++)
        {
            //*w[4 * i + j] = *w[4 * (i - 1) + j] ^ *w[4 * i - 1 + j];
            w[0][4 * i + j] = w[0][4 * (i - 1) + j] ^ w[0][4 * i - 1 + j];
            w[1][4 * i + j] = w[1][4 * (i - 1) + j] ^ w[1][4 * i - 1 + j];
            w[2][4 * i + j] = w[2][4 * (i - 1) + j] ^ w[2][4 * i - 1 + j];
            w[3][4 * i + j] = w[3][4 * (i - 1) + j] ^ w[3][4 * i - 1 + j];
        }
        uint32_t a = (w[0][4 * (i - 1)] << 24) + (w[1][4 * (i - 1)] << 16) + (w[2][4 * (i - 1)] << 8) + w[3][4 * (i - 1)];
        byte* c = G(a);
        for (int k = 0; k < 4; k++)//kΪ����
        {
            w[k][4 * i] = c[k] ^ w[k][4 * i - 1] ^ Rcon[i];
        }
    }
    return w;
}

unsigned char** mingwenshengcheng(unsigned char plaintext[100][256][16]){
  srand((unsigned int)time(NULL));
  for (int i = 0; i < 100; i++)//�����ʼ��Ϊ0
  {
    for (int j = 0; j < 256; j++)
    {
        for (int k = 0; k < 16; k++)
        {
            plaintext[i][j][k] = 0;
        }
    }
   }
for (int i = 0; i < 100; i++)
{
    for (int j = 0; j < 256; j++)
    {
        plaintext[i][j][0] = j;
        for (int k = 1; k < 16; k++)
        {
            plaintext[i][j][k] = rand() % 256;
        }
    }
}
return 0;
}

int main()
{
    //srand((unsigned int)time(NULL));
   unsigned char plaintext[100][256][16];
    //for (int i = 0; i < 100; i++)//�����ʼ��Ϊ0
    //{
    //    for (int j = 0; j < 256; j++)
    //    {
    //        for (int k = 0; k < 16; k++)
    //        {
    //            plaintext[i][j][k] = 0;
    //        }
    //    }
    //}
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            plaintext[i][j][0] = j;
            for (int k = 1; k < 16; k++)
            {
                plaintext[i][j][k] = rand() % 256;
            }
        }
    }

    clock_t starttime, endtime;
    starttime = clock();
    //mi
    unsigned char _state[4][4] = { 0x32,0x30,0x30,0x00,
                      0x30,0x30,0x31,0x00,
                      0x32,0x34,0x32,0x00,
                      0x31,0x36,0x34,0x00 };
    unsigned char** w = KeyExpansion(_state);
    unsigned char** State = new unsigned char* [4];//ͳһ�ɶ���ָ����ʽ
    for (int i = 0; i < 4; i++)
    {
        State[i] = new byte[4];
    }
    for (int m = 0; m < 100; m++) {
        unsigned char mingwen[4][4];
        for (int i = 0; i < 256; i++)
        {
            for (int k = 0; k < 4; k++) {
                for (int v = 0; v < 4; v++) {
                    mingwen[v][k] = plaintext[m][i][4 * k + v];
                    cout << hex << int(mingwen[v][k]) << " ";
                }
                cout << endl;
            }
            unsigned char** mingwen = new unsigned char* [4];
                    //���׶Σ�����Կ��State���С�����Կ�ӡ�
                   byte*** OP = new byte * *[11];
                    for (int j = 0; j < 4; j++)
                    {
                        OP[j] = new byte * [4];
                        for (int k = 0; k < 4; k++)
                        {
                            OP[j][k] = new byte[4];
                        }

                    }
                    OP[0] = AddRoundKey(mingwen, _state);

                    //�м�׶�,ѭ��9�֣��ȹ�S�У�������λ�����л�ϣ��������Կ��
                    /*byte** a = new byte * [4];
                    for (int i = 0; i < 4; i++)
                    {
                        a[i] = new byte[4];
                    }
                    byte** b = new byte * [4];
                    for (int i = 0; i < 4; i++)
                    {
                        b[i] = new byte[4];
                    }*/
                    byte a[4][4], b[4][4];
                    for (int Nr = 0; Nr < 9; Nr++)
                    {
                        //���ֽڹ�S��
                        for (int j = 0; j < 4; j++)
                        {
                            for (int k = 0; k < 4; k++)
                            {
                                a[j][k] = SubBytes(OP[Nr][j][k]);
                                b[j][k] = w[j][(Nr + 1) * k];
                            }

                        }
                        OP[Nr + 1] = AddRoundKey(MixColumns(ShiftRows(a)), b);
                    }
                    //���һ�֣��ȹ�S�У�Ȼ������λ���������Կ�ӣ��������
                    for (int j = 0; j < 4; j++) //������һ������Կ
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            b[j][i] = w[j][40 + i];
                            a[j][i] = SubBytes(OP[9][j][i]);
                        }
                    }
                    OP[10] = AddRoundKey(ShiftRows(a), b);
                    //�������
                    /*cout << "����Ϊ��" << endl;
                    for (int j = 0; j < 4; j++)
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            cout << hex << int(OP[10][j][i]) << " ";
                        }
                        cout << endl;
                    }*/
                    delete w, OP;
                    return **mingwen;
        }

    }
    endtime = clock();
    cout << "ʱ��Ϊ��" << (double)(endtime - starttime)<<"ms";
    return 0;
}
