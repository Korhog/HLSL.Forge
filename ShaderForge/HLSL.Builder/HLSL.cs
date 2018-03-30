using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Values
{
    /// <summary> base type used in DX shaders </summary>
    public enum HLSLValueBaseType
    {
        NONE,
        /// <summary> float </summary>
        FLOAT,
        /// <summary> float </summary>
        FLOAT2,
        /// <summary> float </summary>
        FLOAT3,
        /// <summary> vector 4 </summary>
        FLOAT4,
    }

    public enum HLSLValueSubType
    {
        NONE,
        X_R,
        Y_G,
        Z_B,
        W_A      
    }

    public class HLSLValue
    {
        public HLSLValueBaseType HLSLValueBaseType { get; set; }
        public HLSLValueSubType HLSLValueSubType { get; set; } = HLSLValueSubType.NONE;
    }

    struct HLSLValuePair
    {
        public HLSLValueBaseType From { get; set; }
        public HLSLValueBaseType To { get; set; }
    } 
}
