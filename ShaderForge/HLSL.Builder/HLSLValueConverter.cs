using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Converter
{
    using HLSL.Values;

    public interface IHLSLValueConverter
    {
        string Convert(HLSLValueSubType from, HLSLValueSubType to, object value);
    }    

    abstract class HLSLValueConverterBase : IHLSLValueConverter
    {
        Func<HLSLValueSubType, HLSLValueSubType, object, string> converter;

        public HLSLValueConverterBase(Func<HLSLValueSubType, HLSLValueSubType, object, string> func = null)
        { 
            converter = func;
            if(converter == null)
            {
                converter = (from, to, value) => { return "0"; };
            }
        }

        public string Convert(HLSLValueSubType from, HLSLValueSubType to, object value)
        {
            return converter(from, to, value);
        }
    }

    class HLSLValueConverter: HLSLValueConverterBase
    {
        public HLSLValueConverter(Func<HLSLValueSubType, HLSLValueSubType, object, string> func = null) : base(func)
        {

        }
    }

    public class HLSLValueConverterContainer
    {
        private Dictionary<HLSLValuePair, IHLSLValueConverter> converters;

        private static HLSLValueConverterContainer instance;
        private readonly static object sync = new object();

        public static HLSLValueConverterContainer Current()
        {
            lock(sync)
            {
                if (instance == null)
                    instance = new HLSLValueConverterContainer();
            }

            return instance;
        }

        private HLSLValueConverterContainer()
        {
            converters = new Dictionary<HLSLValuePair, IHLSLValueConverter>();
            InitializeConverters();
        }

        public bool CanConvert(HLSLValueBaseType from, HLSLValueBaseType to)
        {
            var pair = new HLSLValuePair
            {
                From = from,
                To = to
            };
            return CanConvert(pair);
        }

        bool CanConvert(HLSLValuePair pair)       {

            return converters.ContainsKey(pair);
        }

        public string Convert(HLSLValue from, HLSLValue to, object value)
        {
            var pair = new HLSLValuePair
            {
                From = from.HLSLValueBaseType,
                To = to.HLSLValueBaseType
            };

            if (CanConvert(pair))
            {
                var converter = converters[pair];
                return converter.Convert(from.HLSLValueSubType, to.HLSLValueSubType, value);
            }

            return "";            
        }

        private void InitializeConvertersFloatToVector()
        {
            HLSLValuePair pair;
            // float -> float2
            pair = new HLSLValuePair
            {
                From = HLSLValueBaseType.FLOAT,
                To = HLSLValueBaseType.FLOAT2
            };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                switch (from)
                {
                    case HLSLValueSubType.X_R: return string.Format("float2({0}, 0.0f)", value);
                    case HLSLValueSubType.Y_G: return string.Format("float2(0.0f, {0})", value);
                }
                return string.Format("float2({0}, {0})", value);
            });
            // float -> float3
            pair = new HLSLValuePair
            {
                From = HLSLValueBaseType.FLOAT,
                To = HLSLValueBaseType.FLOAT3
            };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                switch (from)
                {
                    case HLSLValueSubType.X_R: return string.Format("float3({0}, 0.0f, 0.0f)", value);
                    case HLSLValueSubType.Y_G: return string.Format("float3(0.0f, {0}, 0.0f)", value);
                    case HLSLValueSubType.Z_B: return string.Format("float3(0.0f, 0.0f, {0})", value);
                }
                return string.Format("float3({0}, {0}, {0})", value);
            });
            // float -> float4
            pair = new HLSLValuePair
            {
                From = HLSLValueBaseType.FLOAT,
                To = HLSLValueBaseType.FLOAT4
            };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                switch (from)
                {
                    case HLSLValueSubType.X_R: return string.Format("float4({0}, 0.0f, 0.0f, 0.0f)", value);
                    case HLSLValueSubType.Y_G: return string.Format("float4(0.0f, {0}, 0.0f, 0.0f)", value);
                    case HLSLValueSubType.Z_B: return string.Format("float4(0.0f, 0.0f, {0}, 0.0f)", value);
                    case HLSLValueSubType.W_A: return string.Format("float4(0.0f, 0.0f, 0.0f, {0})", value);
                }
                return string.Format("float4({0}, {0}, {0}, {0})", value);
            });
        }

        private void InitializeConvertersVectorToVector()
        {
            HLSLValuePair pair; 
            // float2 -> float4
            pair = new HLSLValuePair
            {
                From = HLSLValueBaseType.FLOAT2,
                To = HLSLValueBaseType.FLOAT4
            };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                return string.Format("float4({0}, 0.0f, 1.0f)", value);
            });
            // float3 -> float4
            pair = new HLSLValuePair
            {
                From = HLSLValueBaseType.FLOAT3,
                To = HLSLValueBaseType.FLOAT4
            };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                return string.Format("float4({0}, 1.0f)", value);
            });
            // float4 -> float2, float3 -> float2
            Func<HLSLValueSubType, HLSLValueSubType, object, string> func = (from, to, value) => {
                return string.Format("float2({0}.xy)", value);
            };

            converters[new HLSLValuePair { From = HLSLValueBaseType.FLOAT3, To = HLSLValueBaseType.FLOAT2 }] = new HLSLValueConverter(func);
            converters[new HLSLValuePair { From = HLSLValueBaseType.FLOAT4, To = HLSLValueBaseType.FLOAT2 }] = new HLSLValueConverter(func);

            // float4 -> float3
            pair = new HLSLValuePair { From = HLSLValueBaseType.FLOAT3, To = HLSLValueBaseType.FLOAT4 };
            converters[pair] = new HLSLValueConverter((from, to, value) => {
                return string.Format("float3({0}.xyz)", value);
            });
        }

        private void InitializeConverters()
        {
            InitializeConvertersFloatToVector();
            InitializeConvertersVectorToVector();
        }
    }
}
