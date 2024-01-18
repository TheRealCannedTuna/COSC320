// File: DictionaryBST/DictionaryBST.hpp

#ifndef DICTIONARYBST_HPP_
#define DICTIONARYBST_HPP_

#include "ADictionary.hpp"
#include "BiTreeCSV.hpp"
#include "DictTcontainsVis.hpp"
#include "DictTinsertVis.hpp"
#include "DictTremoveVis.hpp"
#include "BiTCSVclearVis.hpp"
#include "BiTCSVtoStreamVerticalVis.hpp"

// ========= DictionaryBST =========
template <class K, class V>
class DictionaryBST : public ADictionary<K, V> {
private:
    BiTreeCSV< DictPair<K,V> > _tree;

public:
    DictionaryBST() = default;

    void clear() override {
        BiTCSVclearVis< DictPair<K,V> > clearVis;
        _tree.accept(clearVis);
    }

    void insert(K const &key, V const &val) override {
        DictTinsertVis<K, V> dictTinsertVis(key, val);
        _tree.accept(dictTinsertVis);
    }

    bool remove(K const &key, V &val) override {
        DictTremoveVis<K, V> dictTremoveVis(key);
        _tree.accept(dictTremoveVis);
        return dictTremoveVis.result(val);
    }

    bool contains(K const &key, V &val) const override {
        DictTcontainsVis<K, V> dictTcontainsVis(key);
        _tree.accept(dictTcontainsVis);
        return dictTcontainsVis.result(val);
    }

    void toStream(ostream &os) const override {
        BiTCSVtoStreamVerticalVis< DictPair<K, V> > dictTtoStreamVis(os);
        _tree.accept(dictTtoStreamVis);
    }
};

#endif
