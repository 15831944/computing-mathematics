/**
 * @file GeneralFactory.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 广义（一般性）工厂
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __GENERAL_FACTORY_H__
#define __GENERAL_FACTORY_H__

#include <map>

/**
 * @brief 广义工厂 \n 
 * 通过对该工厂进行实例化可得到特定需要的工厂
 * 
 * @tparam AbstractProduct 工厂生成对象的基类
 * @tparam IdentifierType 标识符类型
 * @tparam ProductCreator 返回值为对象指针的函数的函数指针类型（默认为AbstractProduct类型指针）
 */
template <class AbstractProduct, 
          typename IdentifierType,
          typename ProductCreator = AbstractProduct* (*)()>
class Factory {

public:

    /**
     * @brief 注册一个新的对象类型
     * 
     * @param id 标识符
     * @param creator 返回值为该类型对象指针的函数的函数指针
     * @return 注册成功则返回True
     */
    bool Register(const IdentifierType& id, ProductCreator creator) 
    {
        return associations_.insert(AssocPair(id, creator)).second;
    }

    /**
     * @brief 注销已有的对象类型
     * 
     * @param id 注销的对象类型对应的标识符
     * @return 注销成功则返回 Ture
     */
    bool Unregister(const IdentifierType& id) 
    {
        return associations_.erase(id) == 1;
    }

    /**
     * @brief 获取一个新的指定类型对象的指针
     * 
     * @param id 该类型对象对应的标识符
     * @return 该类型对象的指针
     */
    AbstractProduct* CreateObject(const IdentifierType& id) const 
    {
        auto i = associations_.find(id);
        if (i != associations_.end()) 
        {
            return (i->second)();
        }
        // handle error ...
        assert(0 && "Unavaliable Identifier");
    }

    /**
     * @brief 单例模式 (relies on a local static variable) \n 
     * ref 6.4 of Modern C++ design
     * 
     * @return
     */
    static Factory& Instance()
    {
        static Factory obj;
        return obj;
    }

private:

    /**
     * @brief Singleton. \n
     * 防止用户使用构造函数创建新工厂
     * 
     */
    Factory(){;};

    /**
     * @brief Singleton. \n 
     * 防止用户使用拷贝构造函数创建新工厂
     * 
     */
    Factory(const Factory&){;};

    /**
     * @brief Singleton. \n 
     * 防止非法赋值
     * 
     * @return
     */
    Factory& operator=(const Factory &);

    // ~Factory(){;};

    using AssocMap = std::map<IdentifierType, ProductCreator>;

    using AssocPair = std::pair<IdentifierType, ProductCreator>;

    AssocMap associations_;
};

// Factory& Factory::Instance();
// {
//     static Factory obj;
//     return obj;
// }

#endif