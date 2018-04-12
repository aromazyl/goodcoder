/*
 * table.h
 * Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef TABLE_H
#define TABLE_H

#include "trait.h"
#include "type_ops.h"

template <typename...T>
class Table {
public:
  typedef GTR(MakeLists<T...>) FieldTypes;
  typedef GTR(MakePairs<T...>) FieldPairs;

private:
  std::vector<FieldPairs> _datas;

public:
  bool parse_line(const std::string& line) {
    if (line.empty()) {
      return false;
    }
    std::vector<std::string> terms;
    std::string buf;
    for (auto u : line) {
      if (u == '\t') {
        terms.push_back(buf);
        buf.clear();
      } else {
        buf += {u};
      }
    };
    terms.push_back(buf);
    FieldPairs pairs;
    bool ret = Parse<FieldTypes, FieldPairs, 0, GetListLen<FieldTypes>::len>::parse(terms, pairs);
    if (!ret) {
      return false;
    }
    _datas.push_back(pairs);
    return true;
  };

  FieldPairs* get_current_instance() {
    if (_datas.empty()) return NULL;
    return &(*_datas.rbegin());
  }

  size_t size() const {
    return _datas.size();
  }
  FieldPairs* get_instance_by_index(size_t index) {
    assert(index < this->_datas.size());
    if (index < 0 || _datas.empty()) return NULL;
    return &_datas[index];
  }

  template <int i>
  static GTR(GetFromList<FieldTypes, i>)* seek(FieldPairs* instance) {
    return GetFieldData<FieldPairs, GTR(GetFromList<FieldTypes, i>), i>::get(*instance);
  }

};

#define ST_TABLE(...) Table<__VA_ARGS__>
// get table column typelists
#define TABLE_RT(...) typename __VA_ARGS__::FieldTypes;
// get table instance type
#define TABLE_CL(...) typename __VA_ARGS__::FieldPairs;

#endif /* !TABLE_H */
