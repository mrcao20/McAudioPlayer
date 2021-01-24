#include "Service/Utils/McCrypto.h"

#include <string>

#include <aes.h>
#include <filters.h>
#include <hex.h> // StreamTransformationFilter
#include <modes.h>

#ifndef _DEBUG
#include <Python.h>
#endif // !_DEBUG

#include <QDebug>

using namespace CryptoPP;

enum AESKeyLength { AES_KEY_LENGTH_16 = 16, AES_KEY_LENGTH_24 = 24, AES_KEY_LENGTH_32 = 32 };

QString McCrypto::aesEncrypt(const QString &text, const QString &key, const QString &iv)
{
    std::string outData;
    QString inData = PKCS5Padding(text);
    CBC_Mode<AES>::Encryption e;
    e.SetKeyWithIV((byte *) key.toStdString().c_str(),
                   key.size(),
                   (byte *) iv.toStdString().c_str());
    StringSource ss(inData.toStdString(),
                    true,
                    new StreamTransformationFilter(e, new StringSink(outData)));

    QByteArray b(outData.c_str(), static_cast<int>(outData.size()));
    QString outStr = b.toBase64(QByteArray::Base64Encoding);
    return outStr;
}

QString McCrypto::rsaEncrypt(const QString &text, const QString &pubKey, const QString &modulus)
{
    Q_UNUSED(text);
    Q_UNUSED(pubKey);
    Q_UNUSED(modulus);
    const char *cipher = nullptr;
#ifndef _DEBUG
    Py_Initialize(); //使用python之前，要调用Py_Initialize();这个函数进行初始化
    if (!Py_IsInitialized()) {
        qCritical() << "python init failure";
        return "";
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");   //这一步很重要，修改Python路径
    PyObject *pModule = NULL;                      //声明变量
    pModule = PyImport_ImportModule("Encrypt");    //这里是要调用的文件名RSAEncrypt.py
    if (!pModule) {
        qCritical() << "python module load failure";
        return "";
    }
    PyObject *pyRet = PyObject_CallMethod(pModule,
                                          "rsaEncrypt",
                                          "sss",
                                          text.toStdString().c_str(),
                                          pubKey.toStdString().c_str(),
                                          modulus.toStdString().c_str()); //给python函数参数赋值
    PyArg_Parse(pyRet, "s", &cipher);                                     //转换返回类型
    Py_Finalize();
#endif // !_DEBUG
    return QString(cipher);
}

QString McCrypto::getSecretKey(int size)
{
    Q_UNUSED(size);
    const char *key = nullptr;
#ifndef _DEBUG
    Py_Initialize(); //使用python之前，要调用Py_Initialize();这个函数进行初始化
    if (!Py_IsInitialized()) {
        qCritical() << "python init failure";
        return "";
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");   //这一步很重要，修改Python路径
    PyObject *pModule = NULL;                      //声明变量
    pModule = PyImport_ImportModule("Encrypt");    //这里是要调用的文件名RSAEncrypt.py
    if (!pModule) {
        qCritical() << "python module load failure";
        return "";
    }
    PyObject *pyRet = PyObject_CallMethod(pModule, "createSecretKey", "i", 16); //给python函数参数赋值
    PyArg_Parse(pyRet, "s", &key);                                              //转换返回类型
    Py_Finalize();
#endif // !_DEBUG
    return QString(key);
}

QString McCrypto::PKCS5Padding(const QString &text)
{
    QString result = text;
    int pad = 16 - (text.size() % 16);
    for (int i = 0; i < pad; i++) {
        result += QChar(pad);
    }
    return result;
}
