#include <filesystem>

#include "NeuropixAPI.h"

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace Neuropixels
{

static std::filesystem::path this_module_path()
{
#if defined(_WIN32)
    HMODULE h{};
    if (!GetModuleHandleExA(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(&this_module_path),
            &h
        )) {
        throw std::runtime_error("GetModuleHandleEx failed");
    }
    char buf[MAX_PATH];
    if (!GetModuleFileNameA(h, buf, MAX_PATH)) {
        throw std::runtime_error("GetModuleFileName failed");
    }
    return buf;
#else
    Dl_info info{};
    if (!dladdr((void *) &this_module_path, &info) || !info.dli_fname) {
        throw std::runtime_error("dladdr failed");
    }
    return info.dli_fname;
#endif
}

NP_EXPORT NP_ErrorCode NP_APIC np_scanBS()
{
    auto exe_folder = this_module_path().parent_path();
#ifdef OS_WINDOWS
    auto device_manager_dir = exe_folder / "managers";
#elif defined(OS_LINUX)
    auto device_manager_dir = exe_folder / "managers";
#elif defined(OS_MACOS)
    auto device_manager_dir = exe_folder.parent_path() / "PlugIns" / "managers";
#else
    static_assert(false, "Unsupported OS");
#endif
    return scanBS(device_manager_dir.string().c_str());
}

}  // namespace Neuropixels