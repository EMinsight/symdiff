/***
Copyright 2012 Devsim LLC

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

#ifndef TCLCOMMANDS_HH
#define TCLCOMMANDS_HH
#include <tcl.h>
namespace dsTcl {
typedef int (*tclcmd) (ClientData clientData, Tcl_Interp *interp,
      int objc, Tcl_Obj *CONST objv[]);

struct Commands
{
    const char *name;
    tclcmd     command;
};

int Commands_Init(Tcl_Interp *interp);

class dsClientData {
  private:
    dsClientData(const char *name, tclcmd impl) : command_name_(name), command_impl_(impl)
    {
    }

  public:
    static void *CreateData(const char *name, tclcmd impl)
    {

      void *handle;
      handle = new dsClientData(name, impl);
      return handle;
    } 

    static void DeleteData(void *handle)
    {
      delete reinterpret_cast<dsClientData *>(handle);
    }

    static const char *GetCommandName(void *handle)
    {
      return reinterpret_cast<dsClientData *>(handle)->command_name_;
    }

    tclcmd GetCommand() {
      return command_impl_;
    }

  private:
    dsClientData();
    dsClientData(const dsClientData &);
    dsClientData &operator=(const dsClientData &);


    ~dsClientData()
    {
    }

    const char *command_name_;
    tclcmd      command_impl_;
};
}
#endif
