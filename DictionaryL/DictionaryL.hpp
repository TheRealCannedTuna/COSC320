// File: DictionaryL/DictionaryL.hpp

#ifndef DICTIONARYL_HPP_
#define DICTIONARYL_HPP_

#include "ADictionary.hpp"
#include "ListCSV.hpp"
#include "LCSVtoStreamVis.hpp"
#include "LCSVclearVis.hpp"
#include "DictLcontainsVis.hpp"
#include "DictLinsertVis.hpp"
#include "DictLremoveVis.hpp"

// ========= DictionaryL =========
template <class K, class V>
class DictionaryL: public ADictionary<K, V> {
private:
    ListCSV< DictPair<K,V> > _list;

public:
    DictionaryL() = default;

    void clear() override {
        LCSVclearVis< DictPair<K,V> > clearVis;
        _list.accept(clearVis);
    }

    void insert(K const &key, V const &val) override {
        DictLinsertVis<K, V> insertVis(key, val);
        _list.accept(insertVis);
    }

    bool remove(K const &key, V &val) override {
        DictLremoveVis<K, V> removeVis(key);
        _list.accept(removeVis);
        return removeVis.result(val);
    }

    bool contains(K const &key, V &val) const override {
        DictLcontainsVis<K, V> containsVis(key);
        _list.accept(containsVis);
        return containsVis.result(val);
    }

    void toStream(ostream &os) const override {
        os << _list;
    }
};

#endif
