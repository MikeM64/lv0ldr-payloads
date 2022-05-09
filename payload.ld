OUTPUT_FORMAT("binary");

ENTRY(_entry);

_PAYLOAD_START_ = 0x0;

SECTIONS
{
    . = _PAYLOAD_START_;
    .start : {
        *(_start)    
    }
    .text : {
        *(.text)
    }
    .ro : {
        *(.ro)    
    }
}

