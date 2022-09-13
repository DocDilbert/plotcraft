def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c++', '-std=c++20', '-Wall', '-Wextra', '-Werror', 
              '-D_FILE_OFFSET_BITS=64', '-DWXUSINGDLL', '-D__WXMAC__', '-D__WXOSX__','-D__WXOSX_COCOA__',
              '-I/opt/homebrew/lib/wx/include/osx_cocoa-unicode-3.2',
              '-I/opt/homebrew/include/wx-3.2',
              '-I./extern/googletest/googletest/include', 
              '-I./extern/googletest/googlemock/include', 
              '-I./extern/cxxopts/include', 
              '-I./extern/nlohmann_json/include', 
              '-I./extern/fmt/include', 
              '-I./extern/spdlog/include',
              '-I./include', 
            ],
  }
