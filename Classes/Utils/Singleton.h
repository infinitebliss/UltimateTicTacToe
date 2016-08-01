//
//  Singleton.h
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-19.
//
//

#ifndef Singleton_h
#define Singleton_h

template <class T>
class Singleton
{
public:
    static T* Instance() {
        if(!m_pInstance) m_pInstance = new T;
        assert(m_pInstance != NULL);
        return m_pInstance;
    }
    
protected:
    Singleton();
    ~Singleton();
    
private:
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
    static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance=NULL;

#endif /* Singleton_h */
