/***
Copyright 2013 Devsim LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/

#ifndef ORDEREDTABLE_H
#define ORDEREDTABLE_H


#include <memory>
#include "import.hh"
#include <vector>
#include <map>
#include <string>
/*
Get a table representation of an existing expression
*/
namespace Eqo
{
class EquationObject;
typedef std::shared_ptr<EquationObject> EqObjPtr;
}

struct OrderedTableData {
  std::string         value_;
  Eqo::EqObjPtr       ptr_;
  std::vector<size_t> indexes_;
  std::vector<size_t> references_;
};
typedef std::vector<OrderedTableData>  OrderedTable_t;
typedef std::map<std::string, std::vector<size_t> > OrderedIndex_t;

/**
Creates a flat table by doing a depth first search.  Refactor other algorithms use this.
*/
class DLL_PUBLIC ProcessOrderedTable {
  public:
    const std::vector<std::string> &GetErrors() const
    {
      return errors_;
    }

    //// first list is all of our models
    //// second is list of model names we want together
    void run(Eqo::EqObjPtr);
    const OrderedTable_t &GetOrderedTable()
    {
      return orderedTable_;
    }
    const OrderedIndex_t &GetOrderedIndex()
    {
      return orderedIndex_;
    }

  private:
    size_t processOrderedTable(Eqo::EqObjPtr);

    enum ProcessStatus_t {UNTOUCHED = 0, PROCESSING, DONE};

    /// Use this for detecting cycles
    std::map<Eqo::EqObjPtr, ProcessStatus_t> processStatusMap_;
    /// This is the final list that we create as part of the operation
    OrderedTable_t orderedTable_;
    OrderedIndex_t orderedIndex_;
    std::vector<std::string> errors_;
    /// Add index here
};
#endif

