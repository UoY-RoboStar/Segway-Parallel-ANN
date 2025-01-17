theory AnglePIDANN_Circus 
	imports Axiomatic_Circus
begin

subsection \<open> Prelude \<close>

lit_vars
unbundle Circus_Syntax

hide_const (open) sum

subsection \<open> Model \<close>






\<comment> \<open>constant and function declaration\<close>
consts weights :: "real list list list"

consts biases :: "real list list"

consts inRanges :: "(real \<times> real) list"

consts outRanges :: "(real \<times> real) list"

consts annRange :: "(real \<times> real)"


\<comment> \<open>Channel Declaration\<close>
chantype mychan = 
share :: unit
\<comment> \<open>anewError\<close>

anewError :: "real"
	
\<comment> \<open>adiff\<close>

adiff :: "real"
	
\<comment> \<open>angleOutputE\<close>

angleOutputE :: "real"
	
\<comment> \<open>layerRes\<close>

layerRes :: "nat\<times>nat\<times>real"
	
\<comment> \<open>nodeOut\<close>

nodeOut :: "nat\<times>nat\<times>nat\<times>real"
	
\<comment> \<open>terminate\<close>

terminate :: unit 
	


\<comment> \<open>ChannelSet Decleration\<close>

definition relu :: "real \<Rightarrow> real" where
	"relu x = max 0 x"


locale AnglePIDANN
begin

actions  is "(mychan, unit) action" where 
"SSTOP = share  \<rightarrow>  SSTOP" |

"Collator(sum :: real, l :: int, n :: int, i :: int) = ((((l = 0) & ((layerRes!l \<rightarrow> Skip)))
  \<box>
  ((l = 1) & ((nodeOut \<rightarrow> Collator(l,n,i-1,sum + x))))))" | 

"NodeIn(l :: int, n :: int, i :: int) = ((layerRes \<rightarrow> (nodeOut!l \<rightarrow> Skip)))" | 

"Node(l :: int, n :: int, inpSize :: int) = ((( \<interleave> i \<in> {1..inpSize} \<bullet>  NodeIn(l,n,i) )
  \<lbrakk> | \<lbrace> nodeOut \<rbrace> | \<rbrakk> 
  (Collator(l,n,inpSize,0) \<Zhide> \<lbrace> nodeOut \<rbrace>)))" | 

"HiddenLayer(l :: int, s :: int, inpSize :: int) = (( \<lbrakk> \<lbrace> layerRes \<rbrace> \<rbrakk> i \<in> {1..s} \<bullet> Node(l,i,inpSize)))" | 

"HiddenLayers = HiddenLayer(1,1,2)" | 

"OutputLayer = ( \<lbrakk> \<lbrace> layerRes \<rbrace> \<rbrakk> i \<in> {1..1} \<bullet> Node(l,i,1))" | 

"ANN = ((HiddenLayers
  \<lbrakk> | \<lbrace> layerRes \<rbrace> | \<rbrakk> 
  OutputLayer);; ANN)" | 

"Interpreter = ((;; );; Interpreter)" | 

"CircANN = (((Interpreter
  \<lbrakk> | \<lbrace> layerRes \<rbrace> | \<rbrakk> 
  ANN) \<Zhide> \<lbrace> layerRes \<rbrace>) \<triangle> (terminate \<rightarrow> Skip))"

\<comment> \<open>Main action of the process\<close>
definition "ProcDef = cProcess CircANN"

end
 
end





