#include<iostream>
#include<map>

using namespace std;

class MimeType
{
private :
map<string,string> mimeTypes;
public :
MimeType()
{
mimeTypes.insert(pair<string,string>(	"3dmf"		, "x-world/x-3dmf"));
mimeTypes.insert(pair<string,string>(	"3dm"		, "x-world/x-3dmf"));
mimeTypes.insert(pair<string,string>(	"avi"		, "video/x-msvideo"));
mimeTypes.insert(pair<string,string>(	"ai"		, "application/postscript"));
mimeTypes.insert(pair<string,string>(	"bin"		, "application/octet-stream"));
mimeTypes.insert(pair<string,string>(	"bin"		, "application/x-macbinary"));
mimeTypes.insert(pair<string,string>(	"bmp"		, "image/bmp"));
mimeTypes.insert(pair<string,string>(	"cab"		, "application/x-shockwave-flash"));
mimeTypes.insert(pair<string,string>(	"c"		, "text/plain"));
mimeTypes.insert(pair<string,string>(	"c++"		, "text/plain"));
mimeTypes.insert(pair<string,string>(	"class"		, "application/java"));
mimeTypes.insert(pair<string,string>(	"css"		, "text/css"));
mimeTypes.insert(pair<string,string>(	"csv"		, "text/comma-separated-values"));
mimeTypes.insert(pair<string,string>(	"cdr"		, "application/cdr"));
mimeTypes.insert(pair<string,string>(	"doc"		, "application/msword"));
mimeTypes.insert(pair<string,string>(	"dot"		, "application/msword"));
mimeTypes.insert(pair<string,string>(	"docx"		, "application/msword"));
mimeTypes.insert(pair<string,string>(	"dwg"		, "application/acad"));
mimeTypes.insert(pair<string,string>(	"eps"		, "application/postscript"));
mimeTypes.insert(pair<string,string>(	"exe"		, "application/octet-stream"));
mimeTypes.insert(pair<string,string>(	"gif"		, "image/gif"));
mimeTypes.insert(pair<string,string>(	"gz"		, "application/gzip"));
mimeTypes.insert(pair<string,string>(	"gtar"		, "application/x-gtar"));
mimeTypes.insert(pair<string,string>(	"flv"		, "video/x-flv"));
mimeTypes.insert(pair<string,string>(	"fh4"		, "image/x-freehand"));
mimeTypes.insert(pair<string,string>(	"fh5"		, "image/x-freehand"));
mimeTypes.insert(pair<string,string>(	"fhc"		, "image/x-freehand"));
mimeTypes.insert(pair<string,string>(	"help"		, "application/x-helpfile"));
mimeTypes.insert(pair<string,string>(	"hlp"		, "application/x-helpfile"));
mimeTypes.insert(pair<string,string>(	"html"		, "text/html"));
mimeTypes.insert(pair<string,string>(	"htm"		, "text/html"));
mimeTypes.insert(pair<string,string>(	"ico"		, "image/x-icon"));
mimeTypes.insert(pair<string,string>(	"imap"		, "application/x-httpd-imap"));
mimeTypes.insert(pair<string,string>(	"inf"		, "application/inf"));
mimeTypes.insert(pair<string,string>(	"jpe"		, "image/jpeg"));
mimeTypes.insert(pair<string,string>(	"jpeg"		, "image/jpeg"));
mimeTypes.insert(pair<string,string>(	"jpg"		, "image/jpeg"));
mimeTypes.insert(pair<string,string>(	"js"		, "application/x-javascript"));
mimeTypes.insert(pair<string,string>(	"java"		, "text/x-java-source"));
mimeTypes.insert(pair<string,string>(	"latex"		, "application/x-latex"));
mimeTypes.insert(pair<string,string>(	"log"		, "text/plain"));
mimeTypes.insert(pair<string,string>(	"m3u"		, "audio/x-mpequrl"));
mimeTypes.insert(pair<string,string>(	"midi"		, "audio/midi"));
mimeTypes.insert(pair<string,string>(	"mid"		, "audio/midi"));
mimeTypes.insert(pair<string,string>(	"mov"		, "video/quicktime"));
mimeTypes.insert(pair<string,string>(	"mp3"		, "audio/mpeg"));
mimeTypes.insert(pair<string,string>(	"mpeg"		, "video/mpeg"));
mimeTypes.insert(pair<string,string>(	"mpg"		, "video/mpeg"));
mimeTypes.insert(pair<string,string>(	"mp2"		, "video/mpeg"));
mimeTypes.insert(pair<string,string>(	"ogg"		, "application/ogg"));
mimeTypes.insert(pair<string,string>(	"phtml"		, "application/x-httpd-php"));
mimeTypes.insert(pair<string,string>(	"php"		, "application/x-httpd-php"));
mimeTypes.insert(pair<string,string>(	"pdf"		, "application/pdf"));
mimeTypes.insert(pair<string,string>(	"pgp"		, "application/pgp"));
mimeTypes.insert(pair<string,string>(	"png"		, "image/png"));
mimeTypes.insert(pair<string,string>(	"pps"		, "application/mspowerpoint"));
mimeTypes.insert(pair<string,string>(	"ppt"		, "application/mspowerpoint"));
mimeTypes.insert(pair<string,string>(	"ppz"		, "application/mspowerpoint"));
mimeTypes.insert(pair<string,string>(	"pot"		, "application/mspowerpoint"));
mimeTypes.insert(pair<string,string>(	"ps"		, "application/postscript"));
mimeTypes.insert(pair<string,string>(	"qt"		, "video/quicktime"));
mimeTypes.insert(pair<string,string>(	"qd3d"		, "x-world/x-3dmf"));
mimeTypes.insert(pair<string,string>(	"qd3"		, "x-world/x-3dmf"));
mimeTypes.insert(pair<string,string>(	"qxd"		, "application/x-quark-express"));
mimeTypes.insert(pair<string,string>(	"rar"		, "application/x-rar-compressed"));
mimeTypes.insert(pair<string,string>(	"ra"		, "audio/x-realaudio"));
mimeTypes.insert(pair<string,string>(	"ram"		, "audio/x-pn-realaudio"));
mimeTypes.insert(pair<string,string>(	"rm"		, "audio/x-pn-realaudio"));
mimeTypes.insert(pair<string,string>(	"rtf"		, "text/rtf"));
mimeTypes.insert(pair<string,string>(	"spr"		, "application/x-sprite"));
mimeTypes.insert(pair<string,string>(	"sprite"	, "application/x-sprite"));
mimeTypes.insert(pair<string,string>(	"stream"	, "audio/x-qt-stream"));
mimeTypes.insert(pair<string,string>(	"swf"		, "application/x-shockwave-flash"));
mimeTypes.insert(pair<string,string>(	"svg"		, "text/xml-svg"));
mimeTypes.insert(pair<string,string>(	"sgml"		, "text/x-sgml"));
mimeTypes.insert(pair<string,string>(	"sgm"		, "text/x-sgml"));
mimeTypes.insert(pair<string,string>(	"tar"		, "application/x-tar"));
mimeTypes.insert(pair<string,string>(	"tiff"		, "image/tiff"));
mimeTypes.insert(pair<string,string>(	"tif"		, "image/tiff"));
mimeTypes.insert(pair<string,string>(	"tgz"		, "application/x-compressed"));
mimeTypes.insert(pair<string,string>(	"tex"		, "application/x-tex"));
mimeTypes.insert(pair<string,string>(	"txt"		, "text/plain"));
mimeTypes.insert(pair<string,string>(	"vob"		, "video/x-mpg"));
mimeTypes.insert(pair<string,string>(	"wav"		, "audio/x-wav"));
mimeTypes.insert(pair<string,string>(	"wrl"		, "model/vrml"));
mimeTypes.insert(pair<string,string>(	"wrl"		, "x-world/x-vrml"));
mimeTypes.insert(pair<string,string>(	"xla"		, "application/msexcel"));
mimeTypes.insert(pair<string,string>(	"xls"		, "application/msexcel"));
mimeTypes.insert(pair<string,string>(	"xls"		, "application/vnd.ms-excel"));
mimeTypes.insert(pair<string,string>(	"xlc"		, "application/vnd.ms-excel"));
mimeTypes.insert(pair<string,string>(	"xml"		, "text/xml"));
mimeTypes.insert(pair<string,string>(	"zip"		, "application/x-zip-compressed"));
mimeTypes.insert(pair<string,string>(	"zip"		, "application/zip"));
}
string getMimeType(string key)
{
auto it = mimeTypes.find(key);
if(it != mimeTypes.end()) return it -> second ;
return "*/*";
}
};