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
        NONE = 0,

        ADAPTIVE = 1,
        /// <summary> float </summary>
        FLOAT = 2,
        /// <summary> float </summary>
        FLOAT2 = 3,
        /// <summary> float </summary>
        FLOAT3 = 4,
        /// <summary> vector 4 </summary>
        FLOAT4 = 5,
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

    public class HLSLResult
    {
        public string Value { get; set; }
        public HLSLValueBaseType HLSLValueBaseType { get; set; }
        public HLSLValueSubType HLSLValueSubType { get; set; } = HLSLValueSubType.NONE;

        public static HLSLResult Result(string value, HLSLValueBaseType baseType, HLSLValueSubType sub = HLSLValueSubType.NONE)
        {
            return new HLSLResult
            {
                Value = value,
                HLSLValueBaseType = baseType,
                HLSLValueSubType = sub
            };
        }
    }

}
