-- premake5.lua

workspace "CppSnippets"
  language "C++"
  cppdialect "C++20"
  architecture "x64"   
  location "_local" -- where to place sln-files etc
  targetdir "_local/%{cfg.buildcfg}"
  configurations { "Debug", "Final" }
  platforms { "Static" , "DLL" }
  --platforms { "Static" }
  warnings "Extra"
  disablewarnings { "4100" } -- unused parameter value (input to function)

  -- setup the different build configurations
  filter { "platforms:Static" }
    kind "StaticLib"
    defines { "BUILD_COMPILE_STATIC" }

  filter { "platforms:DLL" }
    kind "SharedLib"
    defines { "BUILD_COMPILE_DLL" }   

   filter { "configurations:Debug" }
      defines { "DD_DEBUG", "DEBUG" }
      symbols "On"

   filter {"configurations:Final"}
      defines { "DD_FINAL", "FINAL", "NDEBUG" }
      optimize "On"
      symbols "Off"

      -- Done with global project settings

-- <UtilityFunctions>
function DeclareProject(identifier, projectType)
	project (identifier)
	if projectType ~= nil then kind (projectType) end
	
	files { "source/" .. identifier .. "/**" }
	includedirs { "source/" .. identifier, "source/" .. identifier .. "/Public"  }
	defines("BUILD_" .. string.upper(identifier) .. "_EXPORT") -- example: BUILD_TEMPLATE_EXPORT
end

function DeclareTestProject(identifier)
	project (identifier)
	kind "ConsoleApp"
	
	files { "source/" .. identifier .. "/**" }
	includedirs { "source/" .. identifier, "ExternalLibs/googletest/include" }		
	links { "GoogleTest" }
end

function AddOneDependency(name)
	links { name }
	includedirs { "source/" .. name .. "/Public" }
end

function AddDependency(...)
   local arg = {...}
   for i,v in ipairs(arg) do
      AddOneDependency(v)
   end
end

function UseOneProjectAsInternal(name)
	links { name }
	includedirs { "source/" .. name .. "/Public", "source/" .. name }
	defines("BUILD_" .. string.upper(name) .. "_INTERNAL_ACCESS") -- example: BUILD_TEMPLATE_INTERNAL_ACCESS
end

function UseProjectAsInternal(...)
   local arg = {...}
   for i,v in ipairs(arg) do
      UseOneProjectAsInternal(v)
   end
end

-- <ExternalProjects>
group "_External"
  project "GoogleTest"
    kind "StaticLib"
    files { "ExternalLibs/googletest/src/gtest-all.cc" }
    includedirs { "ExternalLibs/googletest/include", "ExternalLibs/googletest" }

group ""
-- </ExternalProjects>

-- <LibraryProjects>
group "Library"
	DeclareProject("Template")
	
group "Library/Tests"
	DeclareTestProject("Template.Test")
	UseProjectAsInternal("Template")

group "PrevImpl"
	DeclareProject("PrevImpl")
	AddDependency("Template")

group "" -- leave Library-group
-- </LibraryProjects>

-- <TemplateMain>
group "TemplateMain"
	DeclareProject("Execution", "ConsoleApp")
		targetname "MainFoo"
		AddDependency("Template", "PrevImpl")
		filter { "configurations: Debug" }
			defines { "FAKE_LAG" }
		filter {}

group ""
-- </TemplateMain>