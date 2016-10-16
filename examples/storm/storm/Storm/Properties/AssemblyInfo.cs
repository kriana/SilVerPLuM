using System.Reflection;
using System.Runtime.InteropServices;
using Storm.Properties;

[assembly: AssemblyTitle("Storm")]
[assembly: AssemblyDescription("Modding API for Stardew Valley")]
[assembly: AssemblyInformationalVersion(AssemblyInfo.NiceVersion)]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("")]
[assembly: AssemblyProduct("Storm")]
[assembly: AssemblyCopyright("Copyright © Storm 2016")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]
[assembly: Guid(AssemblyInfo.Guid)]
[assembly: AssemblyVersion(AssemblyInfo.Version)]
[assembly: AssemblyFileVersion(AssemblyInfo.Version)]

namespace Storm.Properties
{
    internal static class AssemblyInfo
    {
        public const string Guid = "3ae6190c-1cc7-4fa4-b859-5eabc8ec0614";
        public const string Version = "0.1.1";

        public const string NiceVersion = "Storm " + "v" + Version;
    }
}