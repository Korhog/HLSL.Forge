using System;

using Windows.UI;
using Windows.UI.Xaml.Media;

namespace HLSL.Elements
{
    using Base;
    using HLSL.Converter;
    using HLSL.Values;
    using rMind.Elements;

    using rMind.Nodes;
    using System.Linq;

    public abstract class MathNodeBase : HeaderRowContainerBase, IHLSLEditorNode
    {
        protected Node nodeA;
        protected Node nodeB;
        protected Node output;

        public MathNodeBase(rMindBaseController parent) : base(parent)
        {
            Header = "A * B";            

            nodeA = new Node(this)
            {
                HLSLValueBaseType = Values.HLSLValueBaseType.ADAPTIVE,
                Label = "A",
                Stroke = new SolidColorBrush(Colors.MediumVioletRed),
                UseAccentColor = false,
                ConnectionType = rMindNodeConnectionType.Container,
                NodeOrientation = rMindNodeOriantation.Left,
            };

            output = new Node(this)
            {
                HLSLValueBaseType = Values.HLSLValueBaseType.ADAPTIVE,
                Label = "OUT",
                Stroke = new SolidColorBrush(Colors.MediumVioletRed),
                UseAccentColor = false,
                ConnectionType = rMindNodeConnectionType.Container,
                NodeOrientation = rMindNodeOriantation.Right,
            };

            AddRow(new rMind.Content.Row.rMindRow
            {
                InputNode = nodeA,
                OutputNode = output,
            });

            nodeB = new Node(this)
            {
                HLSLValueBaseType = Values.HLSLValueBaseType.ADAPTIVE,
                Label = "B",
                Stroke = new SolidColorBrush(Colors.MediumVioletRed),
                UseAccentColor = false,
                ConnectionType = rMindNodeConnectionType.Container,
                NodeOrientation = rMindNodeOriantation.Left,
            };

            AddRow(new rMind.Content.Row.rMindRow
            {
                InputNode = nodeB,
                OutputNodeType = rMindNodeConnectionType.None
            });

            CanExpand = false;
            CanEdit = false;
        }

        protected abstract string Result(HLSLResult a, HLSLResult b);

        public override HLSLResult GetNodeValue(Node sender)
        {
            var ResultA = nodeA.GetReverseNodes().Select(x => x as Node).FirstOrDefault()?.GetValue();
            var ResultB = nodeB.GetReverseNodes().Select(x => x as Node).FirstOrDefault()?.GetValue();

            if (ResultA == null || ResultB == null)
            {
                return HLSLResult.Result(null, HLSLValueBaseType.NONE);
            }

            var AResultType = ResultA.HLSLValueBaseType;
            var BResultType = ResultB.HLSLValueBaseType;

            var max = Math.Max((int)AResultType, (int)BResultType);
            var outResult = (HLSLValueBaseType)Enum.GetValues(typeof(HLSLValueBaseType)).GetValue(max);

            var result = string.Format("({0})", Result(ResultA, ResultB));

            var RequireNode = output.GetReverseNodes().Select(x => x as Node).FirstOrDefault();

            if (RequireNode.HLSLValueBaseType == HLSLValueBaseType.ADAPTIVE)
            {
                return HLSLResult.Result(result, outResult);
            }
            else
            {
                if (outResult != RequireNode.HLSLValueBaseType)
                {
                    var converter = HLSLValueConverterContainer.Current();
                    if (converter.CanConvert(outResult, RequireNode.HLSLValueBaseType))
                    {
                        result = converter.Convert(
                            new HLSLResult { Value = result, HLSLValueBaseType = outResult },
                            new HLSLValue { HLSLValueBaseType = RequireNode.HLSLValueBaseType }
                        );
                        return HLSLResult.Result(result, RequireNode.HLSLValueBaseType);
                    }
                    return HLSLResult.Result(null, HLSLValueBaseType.NONE);
                }
            }
            
            return HLSLResult.Result(result, RequireNode.HLSLValueBaseType);
        }
    }
}
