namespace HLSL.Elements.Base
{
    using Values;
    using rMind.Elements;
    using rMind.Nodes;

    /// <summary>
    /// Node для Shader Forge
    /// </summary>
    public class Node : rMindBaseNode
    {
        public HLSLValueBaseType HLSLValueBaseType { get; set; } = HLSLValueBaseType.NONE;
        public HLSLValueSubType HLSLValueSubType { get; set; } = HLSLValueSubType.NONE;

        public Node(rMindBaseElement parent) : base(parent)
        {

        }

        protected override bool ValidateAttach(rMindBaseWireDot dot)
        {
            if (!base.ValidateAttach(dot))
                return false;
            if (dot.ReverseDot.Node != null && dot.ReverseDot.Node is Node)
            {
                Node node = dot.ReverseDot.Node as Node;
                if (HLSLValueBaseType == node.HLSLValueBaseType)
                    return true;

                if (HLSLValueBaseType == HLSLValueBaseType.ADAPTIVE || node.HLSLValueBaseType == HLSLValueBaseType.ADAPTIVE)
                    return true;

                var conv = Converter.HLSLValueConverterContainer.Current();
                return conv.CanConvert(HLSLValueBaseType, node.HLSLValueBaseType);
            }

            return true;
        }

        public virtual HLSLResult GetValue()
        {
            return (Parent as IHLSLEditorNode)?.GetNodeValue(this);
        }
    }
}
