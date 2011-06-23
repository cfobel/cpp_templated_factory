#ifndef ___T_OBJ_FACTORY__HPP___
#define ___T_OBJ_FACTORY__HPP___

#include <map>
#include <exception>
#include <stdexcept>
#include <iostream>


/* Templated factory class taken from:
 * http://www.codeproject.com/KB/architecture/all_kinds_of_factories.aspx?msg=437918#xx437918xx
 */
 
template<class TSrcType>
class TypeID : public std::unary_function<TSrcType, TSrcType> {
public:
     typedef TSrcType objTypeId;
};
 
template<class TKeyType,class TBaseType>
class TObjFactory {
public:
    typedef TBaseType *value_type;
 
    TObjFactory(void) {}
    ~TObjFactory(void) {
        typename typeMapKeyToBuilder::iterator it(m_mapKeyToBuilder.begin()),itend(m_mapKeyToBuilder.end());
        for(;it != itend; ++it)
            delete it->second;
    }

    template<typename TSubType>
    void registerBuilder(const TKeyType &key, TypeID<TSubType> obj) {
        typedef typename TypeID<TSubType>::objTypeId srcType;
        typename typeMapKeyToBuilder::iterator it = m_mapKeyToBuilder.find(key);
        if (it != m_mapKeyToBuilder.end())
            throw std::runtime_error("duplicate");
        m_mapKeyToBuilder[key] = (typeBuilderPtr) new TObjBuilder<srcType>();
    }

    value_type buildObj(const TKeyType &key) {
        typename typeMapKeyToBuilder::iterator it = m_mapKeyToBuilder.find(key);
        if (it == m_mapKeyToBuilder.end())
            throw std::runtime_error("not found");
        return it->second->buildObject();
    }
protected:
    class TObjBuilderBase {
    public:
        virtual value_type buildObject(void) = 0;
    };

    template<class TSubType>
    class TObjBuilder : public TObjBuilderBase {
    public:
        virtual value_type buildObject(void) {
            return new TSubType();
        }
    };

    typedef TObjBuilderBase *typeBuilderPtr;
    typedef std::map<TKeyType, typeBuilderPtr> typeMapKeyToBuilder;
    typeMapKeyToBuilder m_mapKeyToBuilder;
};

#endif
