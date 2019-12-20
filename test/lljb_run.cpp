/*******************************************************************************
 * Copyright (c) 2019, 2019 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include "lljb/Module.hpp"
#include "lljb/Compiler.hpp"
#include "lljb/IRVisitor.hpp"
#include "JitBuilder.hpp"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/SourceMgr.h"

#include <iostream>
#include <cassert>

int main(int argc, char * argv[]){

    bool jitInitialized = initializeJit();
    assert(jitInitialized && "Jit Failed to initialize");

    const char * filename = argv[1]; //todo: better input handling.. this is temporary

    llvm::LLVMContext context;
    llvm::SMDiagnostic SMDiags;
    lljb::Module module(filename, SMDiags, context);

    lljb::Compiler compiler(&module);
    compiler.compile();

    lljb::JittedFunction jc = compiler.getJittedCodeEntry();
    auto result = jc();
    std::cout << "return value: " << result << std::endl;

    shutdownJit();

    return 0;
}
